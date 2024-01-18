#include "FarmingGameInstance.h"

UStaticMesh* UFarmingGameInstance::GetSeedMesh(ESeedType SeedType)
{
	if(SeedActorMeshes.Contains(SeedType))
	{
		return SeedActorMeshes[SeedType];
	}
	return nullptr;
}