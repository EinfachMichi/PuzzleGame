#pragma once

#include "CoreMinimal.h"
#include "FCropInfo.generated.h"

USTRUCT(BlueprintType)
struct PUZZLEGAME_API FCropInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GrowthRatePerMinute;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Mass;
};
