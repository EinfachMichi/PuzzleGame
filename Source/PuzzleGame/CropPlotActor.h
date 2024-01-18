#pragma once

#include "CoreMinimal.h"
#include "ESeedType.h"
#include "Interactable.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "CropPlotActor.generated.h"

constexpr float DEFAULT_GROWTH_STAGE = 0.01f;

UCLASS()
class PUZZLEGAME_API ACropPlotActor : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Crop")
	float GrowthRatePerMinute = 1.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Crop")
	float GrowthState = 0.01f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Crop")
	ESeedType SeedType;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* CropPlotMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* CropMesh;
	
	UBoxComponent* BoxComponent;
	bool Occupied;
	
public:	
	ACropPlotActor();

	virtual void Tick(float DeltaSeconds) override;
	
	bool IsOccupied() const;
	void PlantCrop(ESeedType CropSeedType);
	auto HarvestCrop(OUT ESeedType OldSeedType) -> bool;

private:
	void UpdateGrowthState(float DeltaSeconds);
	
protected:
	virtual void BeginPlay() override;
};
