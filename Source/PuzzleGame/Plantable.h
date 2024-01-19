#pragma once

#include "CoreMinimal.h"
#include "CropActor.h"
#include "ECropType.h"
#include "UObject/Interface.h"
#include "Plantable.generated.h"

UINTERFACE(MinimalAPI)
class UPlantable : public UInterface
{
	GENERATED_BODY()
};

class PUZZLEGAME_API IPlantable
{
	GENERATED_BODY()

protected:
	bool Plantable;
	bool Harvestable;
	
public:
	virtual bool Plant(ECropType CropType) { return false; }
	virtual ACropActor* Harvest() { return nullptr; }
	virtual void InPlantableRange(bool HasEnoughSeeds) {}
	virtual void OutOfPlantableRange() {}
};
