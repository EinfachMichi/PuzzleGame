#include "ItemActor.h"

void AItemActor::BeginPlay()
{
	Super::BeginPlay();
	
	Initialize();
}


void AItemActor::EnterInteractionState()
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

void AItemActor::ExitInteractionState()
{
	if(!MeshComponent)
	{
		return;
	}

	MeshComponent->SetRenderCustomDepth(false);
}

void AItemActor::Initialize()
{
	MeshComponent = FindComponentByClass<UStaticMeshComponent>();
}
