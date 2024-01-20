#include "FarmingGameMode.h"

UStaticMesh* AFarmingGameMode::GetSeedMesh(ECropType CropType)
{
	if(CropInfos.Contains(CropType))
	{
		FCropActorInfo CropInfo = CropInfos[CropType];
		return CropInfo.StaticMesh;
	}
	return nullptr;
}

float AFarmingGameMode::GetGrowthRate(ECropType CropType)
{
	if(CropInfos.Contains(CropType))
	{
		FCropActorInfo CropInfo = CropInfos[CropType];
		return CropInfo.GrowthRatePerMinute;
	}
	return -1;
}

float AFarmingGameMode::GetMass(ECropType CropType)
{
	if(CropInfos.Contains(CropType))
	{
		FCropActorInfo CropInfo = CropInfos[CropType];
		return CropInfo.Mass;
	}
	return -1;
}
