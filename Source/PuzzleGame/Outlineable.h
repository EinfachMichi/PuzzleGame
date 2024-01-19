#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Outlineable.generated.h"

UINTERFACE(MinimalAPI)
class UOutlineable : public UInterface
{
	GENERATED_BODY()
};

class PUZZLEGAME_API IOutlineable
{
	GENERATED_BODY()
	
public:
	virtual void EnableOutline() {}
	virtual void DisableOutline() {}
};
