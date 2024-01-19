#include "PlayerComponent.h"

#include "Interactable.h"

UPlayerComponent::UPlayerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerComponent::BeginPlay()
{
	Super::BeginPlay();

	Initialize();
}

void UPlayerComponent::Initialize()
{
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
	
	if(Debug)
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
		CurrentInteractable->InInteractionRange();

		if(IInteractable* OldInteractable = Cast<IInteractable>(OldLineTraceActor))
		{
			if(CurrentLineTraceActor != OldLineTraceActor)
			{
				OldInteractable->OutOfInteractionRange();
			}
		}
	}
	else
	{
		if(IInteractable* OldInteractable = Cast<IInteractable>(OldLineTraceActor))
		{
			OldInteractable->OutOfInteractionRange();
		}
	}
	OldLineTraceActor = CurrentLineTraceActor;
}

void UPlayerComponent::InteractWithActor()
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

void UPlayerComponent::PickupActor(UPrimitiveComponent* Component)
{
	if(!PhysicsHandle)
	{
		return;
	}
	
	PickedUpActor = Component->GetOwner();
	PickedUpOffset = FVector::Distance(CameraComponent->GetComponentLocation(), LineTraceHitResult.ImpactPoint);
	FVector HitLocation = CameraComponent->GetComponentLocation() + CameraComponent->GetForwardVector() * PickedUpOffset;
	PhysicsHandle->GrabComponentAtLocationWithRotation(Component, NAME_None, HitLocation, FRotator::ZeroRotator);
}

bool UPlayerComponent::TryPickUpActor()
{
	if(!PickedUpActor || !PhysicsHandle)
	{
		return false;
	}

	if(!PhysicsHandle->GrabbedComponent)
	{
		return false;
	}

	FVector NewLocation = CameraComponent->GetComponentLocation() + CameraComponent->GetForwardVector() * PickedUpOffset;
	PhysicsHandle->SetTargetLocation(NewLocation);
	return true;
}

bool UPlayerComponent::TryReleasePickuedUpActor()
{
	if(!PickedUpActor || !PhysicsHandle)
	{
		return false;
	}

	if(!PhysicsHandle->GrabbedComponent)
	{
		return false;
	}
	
	PhysicsHandle->ReleaseComponent();

	if(UStaticMeshComponent* PickedUpActorStaticMeshComponent = PickedUpActor->FindComponentByClass<UStaticMeshComponent>())
	{
		if(PickedUpActorStaticMeshComponent->IsSimulatingPhysics())
		{
			PickedUpActorStaticMeshComponent->SetPhysicsLinearVelocity(
				PickedUpActorStaticMeshComponent->GetPhysicsLinearVelocity() * 0.2f);
		}
	}

	PickedUpActor = nullptr;
	return true;
}

FHitResult UPlayerComponent::GetHitResult()
{
	return LineTraceHitResult;
}
