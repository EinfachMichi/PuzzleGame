#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Windmill.generated.h"

UCLASS()
class PUZZLEGAME_API AWindmill : public AActor
{
	GENERATED_BODY()
	
public:	
	AWindmill();

protected:
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable, Category="Windmill")
	void RotateSail(UStaticMeshComponent* Sail, float RotationSpeed);
};
