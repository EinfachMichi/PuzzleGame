#pragma once

#include "CoreMinimal.h"
#include "PickupableItem.h"
#include "Camera/CameraComponent.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "PlayerComponent.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCurrencyChanged, int, Currency);

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
	float RotationSpeed = 150.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AActor* CurrentLineTraceActor;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AActor* OldLineTraceActor;
	
private:
	UCameraComponent* CameraComponent;
	FHitResult LineTraceHitResult;
	APickupableItem* PickedUpItem;
	float PickedUpOffset;
	FRotator PickedUpItemRotation;
	UPhysicsHandleComponent* PhysicsHandle;

	UPROPERTY(EditAnywhere)
	int Currency;
	
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

	UPROPERTY(BlueprintAssignable)
	FOnCurrencyChanged OnCurrencyChanged;
	
	void PickupItem(APickupableItem* Item);
	UFUNCTION(BlueprintCallable)
	FHitResult GetHitResult();
	APickupableItem* GetPickedUpItem();

	UFUNCTION(BlueprintCallable)
	void AddCurrency(int Value);
	
	void RemoveCurrency(int Value);
	int GetCurrency();
	
private:
	void ShootLineTrace();
	void CheckForHitResultEvents();

protected:
	virtual void BeginPlay() override;
};
