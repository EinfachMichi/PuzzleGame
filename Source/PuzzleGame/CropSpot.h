#pragma once

#include "CoreMinimal.h"
#include "Crop.h"
#include "GameFramework/Actor.h"
#include "CropSpot.generated.h"

UCLASS()
class PUZZLEGAME_API ACropSpot : public AActor
{
	GENERATED_BODY()

	ACrop* CurrentCrop;
	
public:	
	ACropSpot();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void SetCrop(ACrop* Crop);
	bool IsOccupied() const;
};
