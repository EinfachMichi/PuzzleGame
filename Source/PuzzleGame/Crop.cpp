#include "Crop.h"

#include "PlayerComponent.h"

void ACrop::BeginPlay()
{
	Super::BeginPlay();

	CollisionChannel = ECC_Pawn;
	CollisionResponse = ECR_Ignore;
	
	MeshComponent = FindComponentByClass<UStaticMeshComponent>();
	MeshComponent->SetMobility(EComponentMobility::Movable);
	MeshComponent->SetCollisionResponseToChannel(CollisionChannel, CollisionResponse);
	MeshComponent->SetCollisionObjectType(ECC_PhysicsBody);
	MeshComponent->SetGenerateOverlapEvents(true);
}

void ACrop::SetStaticMesh(UStaticMesh* StaticMesh)
{
	if(!StaticMesh)
	{
		return;
	}

	MeshComponent->SetStaticMesh(StaticMesh);
}

UStaticMeshComponent* ACrop::GetStaticMeshComponent()
{
	return MeshComponent;
}

void ACrop::SetMass(float Mass)
{
	if(!MeshComponent)
	{
		return;
	}

	MeshComponent->SetMassOverrideInKg(NAME_None, Mass, true);
}

float ACrop::GetMass()
{
	return MeshComponent->GetMass();
}

void ACrop::SetCropType(ECropType NewCropType)
{
	CropType = NewCropType;
}

ECropType ACrop::GetCropType()
{
	return CropType;
}
