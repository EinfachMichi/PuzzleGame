#pragma once

#include "CoreMinimal.h"
#include "InteractableItem.h"
#include "Shop.generated.h"

UCLASS()
class PUZZLEGAME_API AShop : public AInteractableItem
{
	GENERATED_BODY()

	virtual void Interact(APawn* Pawn) override;
	virtual void BeginPlay() override;
};
