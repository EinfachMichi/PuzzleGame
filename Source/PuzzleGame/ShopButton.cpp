#include "ShopButton.h"

void AShopButton::BeginPlay()
{
	Super::BeginPlay();

	Interactable = true;
}

void AShopButton::Interact(APawn* Pawn)
{
	Super::Interact(Pawn);

	ButtonClicked.Broadcast(Pawn);
}
