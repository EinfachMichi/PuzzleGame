#include "ItemActor.h"

UStaticMeshComponent* AItemActor::GetMesh()
{
	return MeshComponent;
}

void AItemActor::BeginPlay()
{
	Super::BeginPlay();
	
	MeshComponent = FindComponentByClass<UStaticMeshComponent>();
}
