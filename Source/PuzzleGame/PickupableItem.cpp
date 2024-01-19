#include "PickupableItem.h"

void APickupableItem::BeginPlay()
{
	Super::BeginPlay();

	if(MeshComponent)
	{
		MeshComponent->SetSimulatePhysics(true);
	}
}

void APickupableItem::EnableOutline()
{
	if(!MeshComponent)
	{
		return;
	}
	
	MeshComponent->SetCustomDepthStencilValue(3);
	MeshComponent->SetRenderCustomDepth(true);
}

void APickupableItem::DisableOutline()
{
	if(!MeshComponent)
	{
		return;
	}

	MeshComponent->SetRenderCustomDepth(false);
}

void APickupableItem::OnPickedUp()
{
	DisableOutline();
}

void APickupableItem::OnReleased()
{
	EnableOutline();
}

void APickupableItem::ShowInteraction()
{
	EnableOutline();
}

void APickupableItem::HideInteraction()
{
	DisableOutline();
}