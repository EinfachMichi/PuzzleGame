#include "Crate.h"

#include "Crop.h"

ACrate::ACrate()
{
	PrimaryActorTick.bCanEverTick = false;
	
	DefaultSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneComponent"));
	DefaultSceneComponent->SetupAttachment(RootComponent);
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxComponent->SetupAttachment(DefaultSceneComponent);
	BoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	BoxComponent->SetGenerateOverlapEvents(true);
}

void ACrate::OnPickedUp()
{
	Super::OnPickedUp();

	MeshComponent->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Ignore);

	BoxComponent->GetOverlappingActors(ActorsInCrate);
	
	for (AActor* Actor : ActorsInCrate)
	{
		if(ACrop* Crop = Cast<ACrop>(Actor))
		{
			UStaticMeshComponent* CropMesh = Crop->GetStaticMeshComponent();
			if(CropMesh->IsSimulatingPhysics())
			{
				if(CropMesh->GetPhysicsLinearVelocity().Length() <= VelocityThreshold)
				{
					CropMesh->SetSimulatePhysics(false);
					CropMesh->AttachToComponent(DefaultSceneComponent, FAttachmentTransformRules::KeepWorldTransform);
				}
			}
		}
	}
}

void ACrate::OnReleased()
{
	Super::OnReleased();

	MeshComponent->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Block);

	for (AActor* Actor : ActorsInCrate)
	{
		if(ACrop* Crop = Cast<ACrop>(Actor))
		{
			UStaticMeshComponent* CropMesh = Crop->GetStaticMeshComponent();
			CropMesh->SetSimulatePhysics(true);
			CropMesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		}
	}
}