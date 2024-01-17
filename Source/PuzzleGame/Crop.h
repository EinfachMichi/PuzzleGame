#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Crop.generated.h"

UCLASS()
class PUZZLEGAME_API ACrop : public AActor
{
	GENERATED_BODY()
	
public:	
	ACrop();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
