#pragma once

#include "CoreMinimal.h"
#include "ECropType.h"
#include "Engine/GameInstance.h"
#include "FarmingGameInstance.generated.h"

UCLASS()
class PUZZLEGAME_API UFarmingGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Crops")
	TMap<ECropType, UStaticMesh*> CropActorMeshes;

	UPROPERTY(EditAnywhere, Category="Crops")
	TMap<ECropType, float> CropGrowthRates;

public:
	UStaticMesh* GetSeedMesh(ECropType CropType);
	float GetGrowthRate(ECropType CropType);
};
