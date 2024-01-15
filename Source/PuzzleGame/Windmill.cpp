#include "Windmill.h"

AWindmill::AWindmill()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWindmill::BeginPlay()
{
	Super::BeginPlay();
}

void AWindmill::RotateSail(UStaticMeshComponent* Sail, const float RotationSpeed)
{
	const FRotator Rotation = FRotator(RotationSpeed, 0.0f, 0.0f);
	Sail->AddLocalRotation(Rotation);
}
