#pragma once

#include "CoreMinimal.h"
#include "ECropType.h"
#include "FCropInfo.h"
#include "Engine/GameInstance.h"
#include "FarmingGameInstance.generated.h"

UCLASS()
class PUZZLEGAME_API UFarmingGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Farming")
	TMap<ECropType, FCropInfo> CropInfos;

public:
	UStaticMesh* GetSeedMesh(ECropType CropType);
	float GetGrowthRate(ECropType CropType);
	float GetMass(ECropType CropType);
};
