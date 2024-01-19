#include "SeedBagActor.h"

#include "FarmerComponent.h"

void ASeedBagActor::BeginPlay()
{
	Super::BeginPlay();

	Interactable = true;
}

void ASeedBagActor::Interact(APawn* Pawn)
{
	Super::Interact(Pawn);
	
	if(UFarmerComponent* FarmerComponent = Pawn->FindComponentByClass<UFarmerComponent>())
	{
		FarmerComponent->AddSeeds(CropType, SeedCount);
		Destroy();
	}
}