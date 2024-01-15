#pragma once

#include "CoreMinimal.h"
#include "ESeedType.h"
#include "GameFramework/Actor.h"
#include "SeedBag.generated.h"

UCLASS()
class PUZZLEGAME_API ASeedBag : public AActor
{
	GENERATED_BODY()
	
public:	
	ASeedBag();

	UPROPERTY(EditAnywhere, Category="Seed Bag Info")
	int SeedCount;

	UPROPERTY(EditAnywhere, Category="Seed Bag Info")
	ESeedType SeedType;
	
protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category="Custom")
	ESeedType GetSeedType();
};
