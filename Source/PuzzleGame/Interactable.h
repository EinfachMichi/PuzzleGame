#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

class PUZZLEGAME_API IInteractable
{
	GENERATED_BODY()

protected:
	bool Interactable;
	
public:
	virtual void Interact(APawn* Pawn) {}
	virtual void InInteractionRange() {}
	virtual void OutOfInteractionRange() {}
};
