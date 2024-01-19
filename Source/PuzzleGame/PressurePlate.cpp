#include "PressurePlate.h"

#include "Crop.h"

APressurePlate::APressurePlate()
{
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneComponent"));
	DefaultSceneComponent->SetupAttachment(RootComponent);

	PressurePlateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PressurePlateStaticMeshComponent"));
	PressurePlateMesh->SetupAttachment(DefaultSceneComponent);
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollisionComponent"));
	BoxComponent->SetupAttachment(DefaultSceneComponent);
}

float APressurePlate::GetMass()
{
	if(!BoxComponent)
	{
		return -1;
	}
	
	TArray<AActor*> OverlappingActors;
	BoxComponent->GetOverlappingActors(OverlappingActors);

	float Mass = 0;
	for (AActor* Actor : OverlappingActors)
	{
		if(ACrop* Crop = Cast<ACrop>(Actor))
		{
			Mass += Crop->GetMass();
		}
	}
	return Mass;
}
