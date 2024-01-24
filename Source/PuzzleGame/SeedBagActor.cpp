#include "SeedBagActor.h"

#include "FarmerComponent.h"
#include "FarmingGameMode.h"
#include "Kismet/GameplayStatics.h"

void ASeedBagActor::BeginPlay()
{
	Super::BeginPlay();
	
	Interactable = true;
	if(SeedCount == 0)
	{
		SeedCount = 5;
	}
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

void ASeedBagActor::SetCropType(ECropType NewCropType)
{
	this->CropType = NewCropType;

	UpdateMesh(NewCropType);
}

void ASeedBagActor::UpdateMesh(ECropType Type)
{
	if(!MeshComponent)
	{
		return;
	}
	
	if(AFarmingGameMode* GameMode = Cast<AFarmingGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		MeshComponent->SetStaticMesh(GameMode->GetSeedBagMesh(Type));
	}
}
