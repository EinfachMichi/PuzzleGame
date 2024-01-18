#pragma once

#include "CoreMinimal.h"
#include "ESeedType.h"
#include "Engine/GameInstance.h"
#include "FarmingGameInstance.generated.h"

UCLASS()
class PUZZLEGAME_API UFarmingGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Seeds")
	TMap<ESeedType, UStaticMesh*> SeedActorMeshes;

public:
	UStaticMesh* GetSeedMesh(ESeedType SeedType);
};
