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

	Mass = MeshComponent->GetMass();
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

void ACrop::SetMass(float NewMass)
{
	Mass = NewMass;
}

float ACrop::GetMass()
{
	return Mass;
}

void ACrop::SetCropType(ECropType NewCropType)
{
	CropType = NewCropType;
}

ECropType ACrop::GetCropType()
{
	return CropType;
}
