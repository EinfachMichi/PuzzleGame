#pragma once

#include "CoreMinimal.h"
#include "FCropActorInfo.generated.h"

USTRUCT(BlueprintType)
struct PUZZLEGAME_API FCropActorInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GrowthRatePerMinute;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Mass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* SeedBagMesh;
};
