#pragma once

#include "CoreMinimal.h"
#include "ECropType.h"
#include "FCropSeedInfo.h"
#include "PlayerComponent.h"
#include "Components/ActorComponent.h"
#include "FarmerComponent.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlantModeChanged);

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
	FPlantModeChanged PlantModeChanged;

	UPROPERTY(BlueprintReadOnly, Category="Farming")
	bool PlantMode;

private:
	int CurrentCropSeedIndex;
	UPlayerComponent* PlayerComponent;
	AActor* CurrentLineTraceActor;
	AActor* OldLineTraceActor;
	
public:	
	UFarmerComponent();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddSeeds(ECropType CropType, int SeedCount);

	UFUNCTION(BlueprintCallable, Category="Farming")
	void TogglePlantMode();

	UFUNCTION(BlueprintCallable, Category="Farming")
	void PlantSeed();

	UFUNCTION(BlueprintCallable, Category="Farming")
	void HarvestCrop();

	UFUNCTION(BlueprintCallable, Category="Farming")
	int CycleThroughSeedInventory(float Direction);

	UFUNCTION(BlueprintCallable, Category="Farming")
	FCropSeedInfo GetSeedInfo(int Index);
	
private:
	void ManagePlantMode();
	bool HasEnoughSeeds();
	
protected:
	virtual void BeginPlay() override;

};
