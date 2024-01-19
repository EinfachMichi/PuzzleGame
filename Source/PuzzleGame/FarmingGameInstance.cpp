#include "FarmingGameInstance.h"

UStaticMesh* UFarmingGameInstance::GetSeedMesh(ECropType CropType)
{
	if(CropActorMeshes.Contains(CropType))
	{
		return CropActorMeshes[CropType];
	}
	return nullptr;
}

float UFarmingGameInstance::GetGrowthRate(ECropType CropType)
{
	if(CropGrowthRates.Contains(CropType))
	{
		return CropGrowthRates[CropType];
	}
	return -1;
}
