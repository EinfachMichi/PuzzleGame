#pragma once

#include "CoreMinimal.h"
#include "ECropType.h"
#include "Interactable.h"
#include "Plantable.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "CropPlotActor.generated.h"

constexpr float DEFAULT_GROWTH_STAGE = 0.01f;

UCLASS()
class PUZZLEGAME_API ACropPlotActor : public AActor, public IInteractable, public IPlantable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Crops")
	float GrowthRatePerMinute = 1.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Crops")
	float GrowthState = 0.01f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Crops")
	ECropType CropType;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	USceneComponent* DefaultSceneComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* CropPlotMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* CropMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UBoxComponent* BoxComponent;
	bool Occupied;
	
public:	
	ACropPlotActor();

	virtual void Tick(float DeltaSeconds) override;
	
	bool IsOccupied() const;

private:
	void UpdateGrowthState(float DeltaSeconds);
	
protected:
	virtual void BeginPlay() override;
	virtual void EnterInteractionState() override;
	virtual void ExitInteractionState() override;
	
	virtual bool Plant(ECropType NewCropType) override;
	virtual ECropType Harvest() override;
	virtual void EnterPlantableState() override;
	virtual void ExitPlantableState() override;
};
