#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/ActorComponent.h"
#include "PlayerComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUZZLEGAME_API UPlayerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Line Tracing")
	float LineTraceLength = 250.f;

	UPROPERTY(EditAnywhere, Category="Line Tracing")
	bool Debug;
	
private:
	UCameraComponent* CameraComponent;
	FHitResult LineTraceHitResult;
	AActor* CurrentLineTraceActor;
	AActor* OldLineTraceActor;
	AActor* PickedUpActor;
	float PickedUpOffset;
	
public:	
	UPlayerComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category="Interaction")
	void InteractWithActor();

	UFUNCTION(BlueprintCallable, Category="Interaction")
	bool TryPickUpActor();

	UFUNCTION(BlueprintCallable, Category="Interaction")
	bool TryReleasePickuedUpActor();
	
	void PickupActor(AActor* Actor);
	FHitResult GetHitResult();
	
private:
	void Initialize();
	void ShootLineTrace();
	void CheckForHitResultEvents();

protected:
	virtual void BeginPlay() override;
};
