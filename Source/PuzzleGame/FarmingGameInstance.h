#pragma once

#include "CoreMinimal.h"
#include "ECropType.h"
#include "FCropActorInfo.h"
#include "Engine/GameInstance.h"
#include "FarmingGameInstance.generated.h"

UCLASS()
class PUZZLEGAME_API UFarmingGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Farming")
	TMap<ECropType, FCropActorInfo> CropInfos;

public:
	UStaticMesh* GetSeedMesh(ECropType CropType);
	float GetGrowthRate(ECropType CropType);
	float GetMass(ECropType CropType);
};
