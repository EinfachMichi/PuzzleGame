#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "PressurePlate.generated.h"

UCLASS()
class PUZZLEGAME_API APressurePlate : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	USceneComponent* DefaultSceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* PressurePlateMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UBoxComponent* BoxComponent;
	
public:	
	APressurePlate();

	UFUNCTION(BlueprintCallable, Category="Pressure Plate")
	float GetMass();
};
