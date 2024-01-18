#include "SeedBagActor.h"

#include "FarmerComponent.h"

void ASeedBagActor::BeginPlay()
{
	Super::BeginPlay();
}

void ASeedBagActor::Interact(APawn* Pawn)
{
	Super::Interact(Pawn);

	if(UFarmerComponent* FarmerComponent = Pawn->FindComponentByClass<UFarmerComponent>())
	{
		FarmerComponent->AddSeeds(SeedType, SeedCount);
		Destroy();
	}
}