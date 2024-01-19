#pragma once

#include "CoreMinimal.h"
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
	
public:
	virtual bool Plant(ECropType CropType) { return false; }
	virtual ECropType Harvest() { return ECropType::None; }
	virtual void EnterPlantableState(bool HasEnoughSeeds) {}
	virtual void ExitPlantableState() {}
};
