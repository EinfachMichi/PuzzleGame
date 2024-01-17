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

void UPlayerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ShootLineTrace();
	CheckForHitResultEvents();
}

void UPlayerComponent::Initialize()
{
	CameraComponent = GetOwner()->FindComponentByClass<UCameraComponent>();
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
		CurrentInteractable->SetInteractable(true);

		if(IInteractable* OldInteractable = Cast<IInteractable>(OldLineTraceActor))
		{
			if(CurrentLineTraceActor != OldLineTraceActor)
			{
				OldInteractable->SetInteractable(false);
			}
		}
	}
	else
	{
		if(IInteractable* OldInteractable = Cast<IInteractable>(OldLineTraceActor))
		{
			OldInteractable->SetInteractable(false);
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
		Interactable->Interact();
	}
}