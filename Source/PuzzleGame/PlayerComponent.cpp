#include "PlayerComponent.h"

#include "InteractableItem.h"
#include "Outlineable.h"

UPlayerComponent::UPlayerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerComponent::BeginPlay()
{
	Super::BeginPlay();

	CameraComponent = GetOwner()->FindComponentByClass<UCameraComponent>();
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
}

void UPlayerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ShootLineTrace();
	CheckForHitResultEvents();
}

void UPlayerComponent::ShootLineTrace()
{
	AActor* Owner = GetOwner();
	if (!Owner || !CameraComponent)
	{
		return;
	}

	FHitResult HitResult;
	FVector Start = CameraComponent->GetComponentLocation();
	FVector End = Start + CameraComponent->GetForwardVector() * LineTraceLength;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(Owner);
	
	bool Success = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Start,
		End,
		ECC_Visibility,
		CollisionParams
	);

	LineTraceHitResult = HitResult;
	
	if(DebugLineTrace)
	{
		if (Success)
		{
			DrawDebugLine(GetWorld(), Start, HitResult.ImpactPoint, FColor::Green, false, 0, 0, 2);
			DrawDebugPoint(GetWorld(), HitResult.ImpactPoint, 10, FColor::Red, false, 0);
		}
		else
		{
			DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 0, 0, 2);
		}
	}
}

void UPlayerComponent::CheckForHitResultEvents()
{
	CurrentLineTraceActor = LineTraceHitResult.GetActor();

	if(IInteractable* CurrentInteractable = Cast<IInteractable>(CurrentLineTraceActor))
	{
		CurrentInteractable->ShowInteraction();

		if(IInteractable* OldInteractable= Cast<IInteractable>(OldLineTraceActor))
		{
			if(CurrentLineTraceActor != OldLineTraceActor)
			{
				OldInteractable->HideInteraction();
			}
		}
	}
	else
	{
		if(IInteractable* OldInteractable= Cast<IInteractable>(OldLineTraceActor))
		{
			OldInteractable->HideInteraction();
		}
	}
	
	OldLineTraceActor = CurrentLineTraceActor;
}

void UPlayerComponent::Interact()
{
	if(!CurrentLineTraceActor)
	{
		return;
	}

	if(IInteractable* Interactable = Cast<IInteractable>(CurrentLineTraceActor))
	{
		Interactable->Interact(Cast<APawn>(GetOwner()));
	}
}

void UPlayerComponent::PickupItem(APickupableItem* Item)
{
	if(!PhysicsHandle || PickedUpItem)
	{
		return;
	}
	
	PickedUpItem = Item;
	PickedUpOffset = FVector::Distance(CameraComponent->GetComponentLocation(), LineTraceHitResult.GetComponent()->GetComponentLocation());
	FVector HitLocation = LineTraceHitResult.GetComponent()->GetComponentLocation();
	PickedUpItemRotation = Item->GetActorRotation();
	PhysicsHandle->GrabComponentAtLocationWithRotation(PickedUpItem->MeshComponent, NAME_None, HitLocation, PickedUpItemRotation);
	PickedUpItem->MeshComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);;
	PickedUpItem->OnPickedUp();
}

void UPlayerComponent::PickingUpItem()
{
	if(!PhysicsHandle)
	{
		return;
	}
	
	if(!PickedUpItem)
	{
		if(APickupableItem* PickupableItem = Cast<APickupableItem>(CurrentLineTraceActor))
		{
			PickupItem(PickupableItem);
		}
		else
		{
			return;
		}
	}

	if(!PhysicsHandle->GrabbedComponent)
	{
		return;
	}
	
	FVector NewLocation = CameraComponent->GetComponentLocation() + CameraComponent->GetForwardVector() * PickedUpOffset;
	PhysicsHandle->SetTargetLocationAndRotation(NewLocation, PickedUpItemRotation);
}

void UPlayerComponent::ReleaseItem()
{
	if(!PickedUpItem || !PhysicsHandle)
	{
		return;
	}

	if(!PhysicsHandle->GrabbedComponent)
	{
		return;
	}
	
	PhysicsHandle->ReleaseComponent();

	PickedUpItem->MeshComponent->SetPhysicsLinearVelocity(PickedUpItem->MeshComponent->GetPhysicsLinearVelocity() * 0.2f);
	PickedUpItem->MeshComponent->SetCollisionResponseToChannel(PickedUpItem->CollisionChannel, PickedUpItem->CollisionResponse);
	PickedUpItem->OnReleased();
	
	PickedUpItem = nullptr;
}

void UPlayerComponent::RotatePickedUpItem(float Direction)
{
	if (!PickedUpItem)
	{
		return;
	}
		
	FRotator RotationDelta(0.0f, Direction, 0.0f);
	FRotator NewRotation = PickedUpItemRotation + RotationDelta * RotationSpeed * GetWorld()->GetDeltaSeconds();
	
	PickedUpItemRotation = NewRotation;
}

FHitResult UPlayerComponent::GetHitResult()
{
	return LineTraceHitResult;
}

APickupableItem* UPlayerComponent::GetPickedUpItem()
{
	return PickedUpItem;
}

void UPlayerComponent::AddCurrency(int Value)
{
	Currency += Value;
	OnCurrencyChanged.Broadcast(Currency);
}

void UPlayerComponent::RemoveCurrency(int Value)
{
	Currency -= Value;
	OnCurrencyChanged.Broadcast(Currency);
}

int UPlayerComponent::GetCurrency()
{
	return Currency;
}
