#pragma once

#include "CoreMinimal.h"
#include "ECropType.h"
#include "FCropSeedInfo.h"
#include "PlayerComponent.h"
#include "Components/ActorComponent.h"
#include "FarmerComponent.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSeedPlanted);

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSeedsAdded, ECropType, CropType, int, SeedCount);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUZZLEGAME_API UFarmerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Debug")
	bool LogCropSeedInventory;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Farming")
	TArray<FCropSeedInfo> CropSeedInventory;

	UPROPERTY(BlueprintAssignable, Category="Farming")
	FSeedPlanted SeedPlanted;

	UPROPERTY(BlueprintAssignable, Category="Farming")
	FSeedsAdded SeedsAdded;

private:
	int CurrentCropSeedIndex;
	UPlayerComponent* PlayerComponent;
	AActor* CurrentLineTraceActor;
	AActor* OldLineTraceActor;
	
public:	
	UFarmerComponent();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category="Farming")
	void AddSeeds(ECropType CropType, int SeedCount);

	UFUNCTION(BlueprintCallable, Category="Farming")
	void PlantSeed();

	UFUNCTION(BlueprintCallable, Category="Farming")
	void HarvestCrop();

	UFUNCTION(BlueprintCallable, Category="Farming")
	int CycleThroughSeedInventory(float Direction);

	UFUNCTION(BlueprintCallable, Category="Farming")
	FCropSeedInfo GetSeedInfo(int Index);

	UFUNCTION(BlueprintCallable, Category="Farming")
	int GetCurrentSeedCount();

	UFUNCTION(BlueprintCallable, Category="Farming")
	ECropType GetCurrentSeedType();
	
	UFUNCTION(BlueprintCallable, Category="Farming")
	bool HasEnoughSeeds();
	
private:
	void ManageVisuels();
	
protected:
	virtual void BeginPlay() override;

};
