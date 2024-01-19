#pragma once

#include "CoreMinimal.h"
#include "ECropType.h"
#include "PickupableItem.h"
#include "Crop.generated.h"

UCLASS()
class PUZZLEGAME_API ACrop : public APickupableItem
{
	GENERATED_BODY()

private:
	ECropType CropType;
	
protected:
	virtual void BeginPlay() override;

public:
	void SetStaticMesh(UStaticMesh* StaticMesh);
	UStaticMeshComponent* GetStaticMeshComponent();
	
	void SetMass(float Mass);
	float GetMass();

	void SetCropType(ECropType NewCropType);
	ECropType GetCropType();
};
