#pragma once

#include "CoreMinimal.h"
#include "ECropType.h"
#include "FShopItemInfo.generated.h"

USTRUCT(BlueprintType)
struct PUZZLEGAME_API FShopItemInfo
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, Category="Shop")
	UStaticMesh* ItemMesh;

	UPROPERTY(EditAnywhere, Category="Shop")
	int Price;

	UPROPERTY(EditAnywhere, Category="Shop")
	TSubclassOf<AActor> ItemActor;

	UPROPERTY(EditAnywhere, Category="Shop")
	ECropType CropType;
};
