#include "FarmerComponent.h"

#include "FarmingGameInstance.h"

UFarmerComponent::UFarmerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UFarmerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UFarmerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ManageBuildMode();
}

void UFarmerComponent::AddSeeds(ESeedType SeedType, int32 SeedCount)
{
	if(SeedInventory.Contains(SeedType))
	{
		SeedCount += SeedInventory[SeedType];
		SeedInventory[SeedType] = SeedCount;
	}
	SeedInventory.Add(SeedType, SeedCount);

	if(LogSeedInventory)
	{
		UE_LOG(LogTemp, Warning, TEXT("Seed: %s | Count: %i"), ESeedType_Loggable::FHelper::ToString(SeedType), SeedCount);
	}
}

void UFarmerComponent::ToggleBuildMode()
{
	BuildMode = !BuildMode;
	BuildModeChanged.Broadcast();
}

void UFarmerComponent::SetSeedType(ESeedType NewSeedType)
{
	CurrentSeedType = NewSeedType;
}

void UFarmerComponent::ManageBuildMode()
{
	if(!BuildMode)
	{
		return;
	}

	
}