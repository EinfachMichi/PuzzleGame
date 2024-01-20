#pragma once

#include "CoreMinimal.h"
#include "PickupableItem.h"
#include "Camera/CameraComponent.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "PlayerComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUZZLEGAME_API UPlayerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Line Tracing")
	float LineTraceLength = 250.f;

	UPROPERTY(EditAnywhere, Category="Line Tracing")
	bool DebugLineTrace;

	UPROPERTY(EditAnywhere, Category="PickedUp")
	float RotationSpeed = 10.f;

private:
	UCameraComponent* CameraComponent;
	FHitResult LineTraceHitResult;
	AActor* CurrentLineTraceActor;
	AActor* OldLineTraceActor;
	APickupableItem* PickedUpItem;
	float PickedUpOffset;
	FRotator PickedUpItemRotation;
	UPhysicsHandleComponent* PhysicsHandle;
	
public:	
	UPlayerComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category="Interaction")
	void Interact();

	UFUNCTION(BlueprintCallable, Category="Interaction")
	void PickingUpItem();

	UFUNCTION(BlueprintCallable, Category="Interaction")
	void ReleaseItem();

	UFUNCTION(BlueprintCallable, Category="PickedUp")
	void RotatePickedUpItem(float Direction);
	
	void PickupItem(APickupableItem* Item);
	FHitResult GetHitResult();
	APickupableItem* GetPickedUpItem();
	
private:
	void ShootLineTrace();
	void CheckForHitResultEvents();

protected:
	virtual void BeginPlay() override;
};
