#include "FarmingGameInstance.h"

UStaticMesh* UFarmingGameInstance::GetSeedMesh(ECropType SeedType)
{
	if(SeedActorMeshes.Contains(SeedType))
	{
		return SeedActorMeshes[SeedType];
	}
	return nullptr;
}