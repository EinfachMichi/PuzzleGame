#include "FarmerComponent.h"

#include "CropPlot.h"

UFarmerComponent::UFarmerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UFarmerComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerComponent = GetOwner()->FindComponentByClass<UPlayerComponent>();
}

void UFarmerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ManagePlantMode();
}

void UFarmerComponent::AddSeeds(ECropType CropType, int32 SeedCount)
{
	CurrentCropTypeEquipped = CropType;
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

void UFarmerComponent::TogglePlantMode()
{
	if(PlantMode)
	{
		if(ACropPlot* CropPlot = Cast<ACropPlot>(CurrentLineTraceActor))
		{
			CropPlot->UpdatePlantableVisuels(false);
		}
	}
	
	PlantMode = !PlantMode;
	PlantModeChanged.Broadcast();
}

void UFarmerComponent::SetSeedType(ECropType NewCropType)
{
	CurrentCropTypeEquipped = NewCropType;
}

void UFarmerComponent::ManagePlantMode()
{
	if(!PlantMode)
	{
		return;
	}

	CurrentLineTraceActor = PlayerComponent->GetHitResult().GetActor();
	
	if(ACropPlot* CropPlot = Cast<ACropPlot>(CurrentLineTraceActor))
	{
		CropPlot->UpdatePlantableVisuels(true, HasEnoughSeeds());

		if(ACropPlot* OldCropPlot = Cast<ACropPlot>(OldLineTraceActor))
		{
			if(CurrentLineTraceActor != OldLineTraceActor)
			{
				OldCropPlot->UpdatePlantableVisuels(false);
			}
		}
	}
	else
	{
		if(ACropPlot* OldCropPlot = Cast<ACropPlot>(OldLineTraceActor))
		{
			OldCropPlot->UpdatePlantableVisuels(false);
		}
	}
	
	OldLineTraceActor = CurrentLineTraceActor;
}

void UFarmerComponent::HarvestCrop()
{
	if(PlantMode || PlayerComponent->GetPickedUpItem())
	{
		return;
	}

	CurrentLineTraceActor = PlayerComponent->GetHitResult().GetActor();
	
	if(ACropPlot* CropPlot = Cast<ACropPlot>(CurrentLineTraceActor))
	{
		ACrop* Crop = CropPlot->Harvest();
		if(Crop)
		{
			PlayerComponent->PickupItem(Crop);
		}
	}
}

void UFarmerComponent::PlantSeed()
{
	if(!PlantMode || !HasEnoughSeeds())
	{
		return;
	}

	bool Success = false;
	if(ACropPlot* CropPlot = Cast<ACropPlot>(CurrentLineTraceActor))
	{
		Success = CropPlot->Plant(CurrentCropTypeEquipped);
	}

	if(Success)
	{
		CropSeedInventory[CurrentCropTypeEquipped] -= 1;
		if(CropSeedInventory[CurrentCropTypeEquipped] <= 0)
		{
			CropSeedInventory.Remove(CurrentCropTypeEquipped);
			CurrentCropTypeEquipped = ECropType::None;
			//TODO: implement next seed logic
		}
		
		if(LogCropSeedInventory)
		{
			if(CropSeedInventory.Contains(CurrentCropTypeEquipped))
			{
				UE_LOG(LogTemp, Warning, TEXT("Seed: %s | Count: %i"), ECrop_Loggable::FHelper::ToString(CurrentCropTypeEquipped), CropSeedInventory[CurrentCropTypeEquipped]);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("No more seeds in inventory"));
			}
		}
	}
}

bool UFarmerComponent::HasEnoughSeeds()
{
	return CurrentCropTypeEquipped != ECropType::None;
}
