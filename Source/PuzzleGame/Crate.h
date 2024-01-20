#pragma once

#include "CoreMinimal.h"
#include "PickupableItem.h"
#include "Components/BoxComponent.h"
#include "Crate.generated.h"

UCLASS()
class PUZZLEGAME_API ACrate : public APickupableItem
{
	GENERATED_BODY()

public:
	ACrate();

	UPROPERTY(EditAnywhere, Category="Physics")
	float VelocityThreshold = 1.f;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
    USceneComponent* DefaultSceneComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
    UBoxComponent* BoxComponent;

	TArray<AActor*> ActorsInCrate;
	
	virtual void OnPickedUp() override;
	virtual void OnReleased() override;
};
