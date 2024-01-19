#include "InteractableItem.h"

void AInteractableItem::Interact(APawn* Pawn)
{
}

void AInteractableItem::EnableOutline()
{
	if(!MeshComponent)
	{
		return;
	}

	if(Interactable)
	{
		MeshComponent->SetCustomDepthStencilValue(1);
	}
	else
	{
		MeshComponent->SetCustomDepthStencilValue(2);
	}

	MeshComponent->SetRenderCustomDepth(true);
}

void AInteractableItem::DisableOutline()
{
	if(!MeshComponent)
	{
		return;
	}

	MeshComponent->SetRenderCustomDepth(false);
}

void AInteractableItem::ShowInteraction()
{
	EnableOutline();
}

void AInteractableItem::HideInteraction()
{
	DisableOutline();
}
