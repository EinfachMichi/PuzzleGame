#pragma once

#include "CoreMinimal.h"
#include "InteractableItem.h"
#include "ShopButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FButtonClicked, APawn*, Pawn);

UCLASS()
class PUZZLEGAME_API AShopButton : public AInteractableItem
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintAssignable, Category="Events")
	FButtonClicked ButtonClicked;

protected:
	virtual void BeginPlay() override;
	virtual void Interact(APawn* Pawn) override;
};
