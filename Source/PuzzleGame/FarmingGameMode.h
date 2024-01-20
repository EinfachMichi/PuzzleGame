#pragma once

#include "CoreMinimal.h"
#include "ECropType.h"
#include "FCropActorInfo.h"
#include "GameFramework/GameModeBase.h"
#include "FarmingGameMode.generated.h"

UCLASS()
class PUZZLEGAME_API AFarmingGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category="Farming")
	TMap<ECropType, FCropActorInfo> CropInfos;
	
	UStaticMesh* GetSeedMesh(ECropType CropType);
	float GetGrowthRate(ECropType CropType);
	float GetMass(ECropType CropType);
};
