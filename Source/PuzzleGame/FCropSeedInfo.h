#pragma once

#include "CoreMinimal.h"
#include "ECropType.h"
#include "FCropSeedInfo.generated.h"

USTRUCT(BlueprintType)
struct PUZZLEGAME_API FCropSeedInfo
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECropType CropType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SeedCount;

	bool operator==(const FCropSeedInfo& Other) const
	{
		return CropType == Other.CropType && SeedCount == Other.SeedCount;
	}

	bool operator==(ECropType Crop) const
	{
		return CropType == Crop;
	}
};
