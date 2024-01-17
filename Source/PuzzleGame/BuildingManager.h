#pragma once

#include "CoreMinimal.h"
#include "CropSpot.h"
#include "Components/ActorComponent.h"
#include "BuildingManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUZZLEGAME_API UBuildingManager : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Debug")
	bool Debug = false;

	TArray<ACropSpot*> CropSpots;

public:	
	UBuildingManager();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable, Category="Utils")
	FHitResult GetLineTraceHitResult(FVector WorldLocation, FVector ForwardVector, float Distance);
};
