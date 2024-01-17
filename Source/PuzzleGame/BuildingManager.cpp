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

	CameraComponent = GetOwner()->FindComponentByClass<UCameraComponent>();
}

void UBuildingManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ShootLineTrace();
	PreviewPlaceableActor();
}

FHitResult UBuildingManager::GetLineTraceHitResult()
{
	return LineTraceHitResult;
}

void UBuildingManager::SetActorToPlace(AActor* Actor)
{
	this->ActorToPlaceTemplate = Actor;
}

void UBuildingManager::PlaceActor()
{
	if(ActorToPlace)
	{
		UE_LOG(LogTemp, Error, TEXT("Actor successfully placed"));
		UE_LOG(LogTemp, Error, TEXT("Weird: %s"), *ActorToPlace->GetName());
		ActorToPlace = nullptr;
	}
}

void UBuildingManager::PreviewPlaceableActor()
{
	if(!ActorToPlaceTemplate || !CanPlaceMaterial || !CanNotPlaceMaterial)
	{
		return;
	}

	if(!ActorToPlace)
	{
		UClass* ActorClass = ActorToPlaceTemplate->GetClass();
		FVector ActorLocation = ActorToPlaceTemplate->GetActorLocation();
		FRotator ActorRotation = ActorToPlaceTemplate->GetActorRotation();
		FActorSpawnParameters SpawnParameters;
		ActorToPlace = GetWorld()->SpawnActor<AActor>(ActorClass, ActorLocation, ActorRotation, SpawnParameters);
	}

	
}

void UBuildingManager::ShootLineTrace()
{
	FHitResult HitResult;
	
	AActor* Owner = GetOwner();
	if (!Owner || !CameraComponent)
	{
		return;
	}
	
	FVector Start = CameraComponent->GetComponentLocation();
	FVector End = Start + CameraComponent->GetForwardVector() * LineTraceDistance;
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
