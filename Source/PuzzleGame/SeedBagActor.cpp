#include "SeedBagActor.h"
#include "FarmerComponent.h"
#include "Kismet/GameplayStatics.h"

void ASeedBagActor::BeginPlay()
{
	Super::BeginPlay();

	Initialize();
}

void ASeedBagActor::Interact()
{
	Super::Interact();
	
	if(!FarmerComponent)
	{
		return;
	}

	FarmerComponent->AddSeeds(SeedType, SeedCount);
	Destroy();
}

void ASeedBagActor::Initialize()
{
	UFarmerComponent* FarmerComponentFromPlayerController = nullptr;
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	if (PlayerController)
	{
		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

		if (PlayerPawn)
		{
			FarmerComponentFromPlayerController = PlayerPawn->FindComponentByClass<UFarmerComponent>();
		}
	}
	this->FarmerComponent = FarmerComponentFromPlayerController;
}
