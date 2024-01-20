#pragma once

#include "Audio.h"
#include "CoreMinimal.h"
#include "Crop.h"
#include "ECropType.h"
#include "Interactable.h"
#include "Outlineable.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "CropPlot.generated.h"

constexpr float DEFAULT_GROWTH_STATE = 0.01f;

UCLASS()
class PUZZLEGAME_API ACropPlot : public AActor, public IOutlineable, public IInteractable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Farming")
	float GrowthRatePerMinute = 1.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Farming")
	float GrowthState = DEFAULT_GROWTH_STATE;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Farming")
	ECropType CropType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Farming")
	float CropMass;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	USceneComponent* DefaultSceneComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* CropPlotMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* CropMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, Category="Audio")
	USoundWave* SmallCropSound;

	UPROPERTY(EditAnywhere, Category="Audio")
	USoundWave* BigCropSound;
	
	UActorComponent* NiagaraHarvestEffect;

	UAudioComponent* HarvestSoundAudioComponent;
	
	bool Occupied;
	
public:	
	ACropPlot();

	virtual void Tick(float DeltaSeconds) override;

	bool Plant(ECropType NewCropType);
	ACrop* Harvest();
	void UpdatePlantableVisuels(bool Enabled, bool Requirement = false);

private:
	void UpdateGrowthState(float DeltaSeconds);
	bool IsHarvestable();
	
protected:
	virtual void BeginPlay() override;

	virtual void ShowInteraction() override;
	virtual void HideInteraction() override;
	
	virtual void EnableOutline() override;
	virtual void DisableOutline() override;
};
