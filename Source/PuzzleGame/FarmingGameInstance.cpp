#include "FarmingGameInstance.h"

UStaticMesh* UFarmingGameInstance::GetSeedMesh(ECropType CropType)
{
	if(CropInfos.Contains(CropType))
	{
		FCropActorInfo CropInfo = CropInfos[CropType];
		return CropInfo.StaticMesh;
	}
	return nullptr;
}

float UFarmingGameInstance::GetGrowthRate(ECropType CropType)
{
	if(CropInfos.Contains(CropType))
	{
		FCropActorInfo CropInfo = CropInfos[CropType];
		return CropInfo.GrowthRatePerMinute;
	}
	return -1;
}

float UFarmingGameInstance::GetMass(ECropType CropType)
{
	if(CropInfos.Contains(CropType))
	{
		FCropActorInfo CropInfo = CropInfos[CropType];
		return CropInfo.Mass;
	}
	return -1;
}
