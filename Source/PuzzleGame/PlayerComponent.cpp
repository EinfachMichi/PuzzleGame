#include "PlayerComponent.h"

#include "Interactable.h"

UPlayerComponent::UPlayerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPlayerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FHitResult HitResult = LineTrace();
	if(HitResult.GetActor())
	{
		if(HitResult.GetActor()->Implements<IInteractable>())
		{
			UE_LOG(LogTemp, Warning, TEXT("We have hit an actor."))
		}
	}
}

FHitResult UPlayerComponent::LineTrace()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * LineTraceDistance;

	FHitResult HitResult;
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor::Black, false, 0.0f, 0.f, 10.f);
	
	GetWorld()->LineTraceSingleByObjectType(
		HitResult,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECC_WorldStatic),
		TraceParameters
	);
	return HitResult;
}

