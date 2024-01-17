#include "ItemActor.h"

void AItemActor::BeginPlay()
{
	Super::BeginPlay();
	
	Initialize();
}


void AItemActor::Interact()
{
	
}

void AItemActor::SetInteractable(bool Interactable)
{
	if(!MeshComponent)
	{
		return;
	}

	MeshComponent->SetRenderCustomDepth(Interactable);
}

void AItemActor::Initialize()
{
	MeshComponent = FindComponentByClass<UStaticMeshComponent>();
}