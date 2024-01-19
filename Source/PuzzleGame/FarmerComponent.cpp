#include "FarmerComponent.h"

#include "FarmingGameInstance.h"
#include "Plantable.h"

UFarmerComponent::UFarmerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UFarmerComponent::BeginPlay()
{
	Super::BeginPlay();

	Initialize();
}

void UFarmerComponent::Initialize()
{
	PlayerComponent = GetOwner()->FindComponentByClass<UPlayerComponent>();
}

void UFarmerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ManageBuildMode();
}

void UFarmerComponent::AddSeeds(ECropType CropType, int32 SeedCount)
{
	CurrentCropType = CropType;
	if(CropSeedInventory.Contains(CropType))
	{
		SeedCount += CropSeedInventory[CropType];
		CropSeedInventory[CropType] = SeedCount;
	}
	CropSeedInventory.Add(CropType, SeedCount);

	if(LogCropSeedInventory)
	{
		UE_LOG(LogTemp, Warning, TEXT("Seed: %s | Count: %i"), ECrop_Loggable::FHelper::ToString(CropType), SeedCount);
	}
}

void UFarmerComponent::ToggleBuildMode()
{
	if(BuildMode)
	{
		if(IPlantable* CurrentPlantable = Cast<IPlantable>(CurrentLineTraceActor))
		{
			CurrentPlantable->ExitPlantableState();
		}
	}
	
	BuildMode = !BuildMode;
	BuildModeChanged.Broadcast();
}

void UFarmerComponent::SetSeedType(ECropType NewCropType)
{
	CurrentCropType = NewCropType;
}

void UFarmerComponent::ManageBuildMode()
{
	if(!BuildMode)
	{
		return;
	}

	CurrentLineTraceActor = PlayerComponent->GetHitResult().GetActor();
	
	if(IPlantable* CurrentPlantable = Cast<IPlantable>(CurrentLineTraceActor))
	{
		CurrentPlantable->EnterPlantableState(CurrentCropType != ECropType::None);

		if(IPlantable* OldInteractable = Cast<IPlantable>(OldLineTraceActor))
		{
			if(CurrentLineTraceActor != OldLineTraceActor)
			{
				OldInteractable->ExitPlantableState();
			}
		}
	}
	else
	{
		if(IPlantable* OldInteractable = Cast<IPlantable>(OldLineTraceActor))
		{
			OldInteractable->ExitPlantableState();
		}
	}
	
	OldLineTraceActor = CurrentLineTraceActor;
}

bool UFarmerComponent::TryPlantSeed()
{
	if(!BuildMode || CurrentCropType == ECropType::None)
	{
		return false;
	}

	bool Success = false;
	if(IPlantable* Plantable = Cast<IPlantable>(CurrentLineTraceActor))
	{
		Success = Plantable->Plant(CurrentCropType);
	}

	if(Success)
	{
		CropSeedInventory[CurrentCropType] -= 1;
		if(CropSeedInventory[CurrentCropType] <= 0)
		{
			CropSeedInventory.Remove(CurrentCropType);
			CurrentCropType = ECropType::None;
			//TODO: implement next seed logic
		}
		
		if(LogCropSeedInventory)
		{
			if(CropSeedInventory.Contains(CurrentCropType))
			{
				UE_LOG(LogTemp, Warning, TEXT("Seed: %s | Count: %i"), ECrop_Loggable::FHelper::ToString(CurrentCropType), CropSeedInventory[CurrentCropType]);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("No more seeds in inventory"));
			}
		}
	}

	return Success;
}