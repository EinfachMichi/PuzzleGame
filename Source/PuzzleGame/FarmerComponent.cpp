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

void UFarmerComponent::AddSeeds(ECropType CropType, int SeedCount)
{
	for (FCropSeedInfo& SeedInfo : CropSeedInventory)
	{
		if(SeedInfo.CropType == CropType)
		{
			SeedInfo.SeedCount += SeedCount;
			SeedsAdded.Broadcast(SeedInfo.CropType, SeedInfo.SeedCount);
			return;
		}
	}
	
	FCropSeedInfo NewSeedInfo;
	NewSeedInfo.CropType = CropType;
	NewSeedInfo.SeedCount = SeedCount;
	
	CropSeedInventory.Add(NewSeedInfo);
	CurrentCropSeedIndex = CropSeedInventory.Num() - 1;
	SeedsAdded.Broadcast(CropType, SeedCount);
	
	if(LogCropSeedInventory)
	{
		UE_LOG(LogTemp, Warning, TEXT("Seed: %s | Count: %i"), ECrop_Loggable::FHelper::ToString(CropType), SeedCount);
	}
}

void UFarmerComponent::PlantSeed()
{
	if(!PlantMode || !HasEnoughSeeds())
	{
		return;
	}

	CurrentLineTraceActor = PlayerComponent->GetHitResult().GetActor();
	
	if(ACropPlot* CropPlot = Cast<ACropPlot>(CurrentLineTraceActor))
	{
		if(!CropPlot->IsOccupied())
		{
			bool RemoveSeedInfo = false;
			FCropSeedInfo SeedInfoToRemove;
			for (FCropSeedInfo& SeedInfo : CropSeedInventory)
			{
				if(SeedInfo.CropType == CropSeedInventory[CurrentCropSeedIndex].CropType)
				{
					if(CropPlot->Plant(CropSeedInventory[CurrentCropSeedIndex].CropType))
					{
						SeedInfo.SeedCount -= 1;
						if(SeedInfo.SeedCount <= 0)
						{
							SeedInfoToRemove = SeedInfo;
							RemoveSeedInfo = true;
							break;
						}

						if (LogCropSeedInventory)
						{
							UE_LOG(LogTemp, Warning, TEXT("Seed: %s | Count: %i"),
								ECrop_Loggable::FHelper::ToString(CropSeedInventory[CurrentCropSeedIndex].CropType), SeedInfo.SeedCount);
						}
					}
				}
			}

			if(RemoveSeedInfo)
			{
				CropSeedInventory.Remove(SeedInfoToRemove);
				CycleThroughSeedInventory(1);
			}
		
			SeedPlanted.Broadcast();	
		}
	}
}

int UFarmerComponent::CycleThroughSeedInventory(float Direction)
{
	if(CropSeedInventory.Num() <= 0 || !PlantMode)
	{
		return -1;
	}
	
	int NextIndex = CurrentCropSeedIndex + Direction;
	if(NextIndex < 0)
	{
		NextIndex = CropSeedInventory.Num() - 1;
	}
	else if(NextIndex >= CropSeedInventory.Num())
	{
		NextIndex = 0;
	}

	CurrentCropSeedIndex = NextIndex;
	return CurrentCropSeedIndex;
}

FCropSeedInfo UFarmerComponent::GetSeedInfo(int Index)
{
	if(CropSeedInventory.Num() < Index || CropSeedInventory.Num() == 0)
	{
		return FCropSeedInfo();
	}
	return CropSeedInventory[Index];
}

int UFarmerComponent::GetCurrentSeedCount()
{
	if(CropSeedInventory.Num() <= CurrentCropSeedIndex)
	{
		return -1;
	}
	return CropSeedInventory[CurrentCropSeedIndex].SeedCount;
}

ECropType UFarmerComponent::GetCurrentSeedType()
{
	if(CropSeedInventory.Num() < CurrentCropSeedIndex || CropSeedInventory.Num() == 0)
	{
		return ECropType::None;
	}
	return CropSeedInventory[CurrentCropSeedIndex].CropType;
}

bool UFarmerComponent::HasEnoughSeeds()
{
	if(CropSeedInventory.Num() < CurrentCropSeedIndex || CropSeedInventory.Num() == 0)
	{
		return false;
	}
	
	return CropSeedInventory[CurrentCropSeedIndex].SeedCount > 0;
}
