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
	UPROPERTY(EditAnywhere, Category="Seeds")
	TMap<ECropType, UStaticMesh*> SeedActorMeshes;

public:
	UStaticMesh* GetSeedMesh(ECropType SeedType);
};
