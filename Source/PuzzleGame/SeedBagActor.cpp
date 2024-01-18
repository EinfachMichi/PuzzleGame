#include "SeedBagActor.h"

void ASeedBagActor::BeginPlay()
{
	Super::BeginPlay();
}

void ASeedBagActor::Interact()
{
	Super::Interact();

	Destroy();
}