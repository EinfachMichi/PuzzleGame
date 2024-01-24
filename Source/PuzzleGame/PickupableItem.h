#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "ItemActor.h"
#include "Outlineable.h"
#include "PickupableItem.generated.h"

UCLASS()
class PUZZLEGAME_API APickupableItem : public AItemActor, public IOutlineable, public IInteractable
{
	GENERATED_BODY()

public:
	ECollisionChannel CollisionChannel = ECC_Pawn;
	ECollisionResponse CollisionResponse = ECR_Ignore;

	virtual void OnPickedUp();
	virtual void OnReleased();
	
protected:
	virtual void BeginPlay() override;
	
	virtual void EnableOutline() override;
	virtual void DisableOutline() override;

	virtual void ShowInteraction() override;
	virtual void HideInteraction() override;
};