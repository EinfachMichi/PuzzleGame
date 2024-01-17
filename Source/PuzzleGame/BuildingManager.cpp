#include "BuildingManager.h"

#include "EngineUtils.h"

UBuildingManager::UBuildingManager()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBuildingManager::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<ACropSpot> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ACropSpot* CropSpot = *ActorItr;
		if (CropSpot)
		{
			CropSpots.Add(CropSpot);
		}
	}
}

void UBuildingManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

FHitResult UBuildingManager::GetLineTraceHitResult(FVector WorldLocation, FVector ForwardVector, float Distance)
{
	FHitResult HitResult;
	
	AActor* Owner = GetOwner();
	if (!Owner)
	{
		return HitResult;
	}
	
	FVector EndTrace = WorldLocation + ForwardVector * Distance;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(Owner);
	
	bool Success = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		WorldLocation,
		EndTrace,
		ECC_PhysicsBody,
		CollisionParams
	);

	if(Debug)
	{
		if (Success)
		{
			DrawDebugLine(GetWorld(), WorldLocation, HitResult.ImpactPoint, FColor::Green, false, 0, 0, 2);
			DrawDebugPoint(GetWorld(), HitResult.ImpactPoint, 10, FColor::Red, false, 0);
		}
		else
		{
			DrawDebugLine(GetWorld(), WorldLocation, EndTrace, FColor::Red, false, 0, 0, 2);
		}
	}
	
	return HitResult;
}