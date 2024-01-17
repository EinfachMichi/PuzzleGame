#include "BuildingManager.h"

UBuildingManager::UBuildingManager()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBuildingManager::BeginPlay()
{
	Super::BeginPlay();
}

void UBuildingManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}