#pragma once

#include "CoreMinimal.h"
#include "ECropType.h"
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
	TMap<ECropType, int32> CropSeedInventory;

	UPROPERTY(BlueprintAssignable, Category="Farming")
	FPlantModeChanged PlantModeChanged;

	UPROPERTY(BlueprintReadOnly, Category="Farming")
	bool PlantMode;

private:
	ECropType CurrentCropType;
	UPlayerComponent* PlayerComponent;
	AActor* CurrentLineTraceActor;
	AActor* OldLineTraceActor;
	
public:	
	UFarmerComponent();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddSeeds(ECropType CropType, int32 SeedCount);

	UFUNCTION(BlueprintCallable, Category="Farming")
	void TogglePlantMode();

	UFUNCTION(BlueprintCallable, Category="Farming")
	void SetSeedType(ECropType NewCropType);

	UFUNCTION(BlueprintCallable, Category="Farming")
	bool TryPlantSeed();

	UFUNCTION(BlueprintCallable, Category="Farming")
	bool TryHarvestCrop();
	
private:
	void Initialize();
	void ManagePlantMode();
	
protected:
	virtual void BeginPlay() override;

};
