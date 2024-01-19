#include "ItemActor.h"

void AItemActor::BeginPlay()
{
	Super::BeginPlay();
	
	MeshComponent = FindComponentByClass<UStaticMeshComponent>();
}