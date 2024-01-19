#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "ItemActor.h"
#include "Outlineable.h"
#include "InteractableItem.generated.h"

UCLASS()
class PUZZLEGAME_API AInteractableItem : public AItemActor, public IOutlineable, public IInteractable
{
	GENERATED_BODY()

protected:
	bool Interactable;

	void virtual Interact(APawn* Pawn) override;
	
	virtual void EnableOutline() override;
	virtual void DisableOutline() override;

	virtual void ShowInteraction() override;
	virtual void HideInteraction() override;
};
