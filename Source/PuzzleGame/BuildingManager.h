#pragma once

#include "CoreMinimal.h"
#include "CropSpot.h"
#include "Camera/CameraComponent.h"
#include "Components/ActorComponent.h"
#include "BuildingManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUZZLEGAME_API UBuildingManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Utils")
	float LineTraceDistance;

	UPROPERTY(BlueprintReadOnly, Category="Utils")
	FHitResult LineTraceHitResult;
	
private:
	UPROPERTY(EditAnywhere, Category="Debug")
	bool Debug = false;

	UPROPERTY(EditAnywhere, Category="Build System")
	UMaterialInstance* CanPlaceMaterial;
	
	UPROPERTY(EditAnywhere, Category="Build System")
	UMaterialInstance* CanNotPlaceMaterial;

	AActor* ActorToPlaceTemplate;
	AActor* ActorToPlace;
	UCameraComponent* CameraComponent;
	TArray<ACropSpot*> CropSpots;

public:	
	UBuildingManager();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable, Category="Utils")
	FHitResult GetLineTraceHitResult();
	
	UFUNCTION(BlueprintCallable, Category="Build System")
	void SetActorToPlace(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category="Build System")
	void PlaceActor();
	
private:
	void PreviewPlaceableActor();
	void ShootLineTrace();

protected:
	virtual void BeginPlay() override;
};
