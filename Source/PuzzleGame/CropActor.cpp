#include "CropActor.h"

#include "PlayerComponent.h"

void ACropActor::BeginPlay()
{
	Super::BeginPlay();
	
	StaticMeshComponent = FindComponentByClass<UStaticMeshComponent>();
	StaticMeshComponent->SetMobility(EComponentMobility::Movable);
	StaticMeshComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
}

void ACropActor::Interact(APawn* Pawn)
{
	if(UPlayerComponent* PlayerComponent = Pawn->FindComponentByClass<UPlayerComponent>())
	{
		PlayerComponent->PickupActor(StaticMeshComponent);
	}
}

void ACropActor::InInteractionRange()
{
	if(!StaticMeshComponent)
	{
		return;
	}

	StaticMeshComponent->SetRenderCustomDepth(true);
	StaticMeshComponent->SetCustomDepthStencilValue(3);
	StaticMeshComponent->SetSimulatePhysics(true);
}

void ACropActor::OutOfInteractionRange()
{
	if(!StaticMeshComponent)
	{
		return;
	}

	StaticMeshComponent->SetRenderCustomDepth(false);
}

void ACropActor::SetStaticMesh(UStaticMesh* StaticMesh)
{
	if(!StaticMesh)
	{
		return;
	}

	StaticMeshComponent->SetStaticMesh(StaticMesh);
}

UStaticMeshComponent* ACropActor::GetStaticMeshComponent()
{
	return StaticMeshComponent;
}
