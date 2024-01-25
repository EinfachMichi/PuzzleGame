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
	float Mass;
	
protected:
	virtual void BeginPlay() override;

public:
	void SetStaticMesh(UStaticMesh* StaticMesh);
	UStaticMeshComponent* GetStaticMeshComponent();
	
	void SetMass(float NewMass);
	UFUNCTION(BlueprintCallable)
	float GetMass();

	void SetCropType(ECropType NewCropType);
	UFUNCTION(BlueprintCallable)
	ECropType GetCropType();

	bool IsBig();

};
