#include "Shop.h"

#include "PlayerComponent.h"

void AShop::Interact(APawn* Pawn)
{
	Super::Interact(Pawn);
	
	if(UPlayerComponent* PlayerComponent = Pawn->FindComponentByClass<UPlayerComponent>())
	{
		FHitResult HitResult = PlayerComponent->GetHitResult();
		UE_LOG(LogTemp, Warning, TEXT("%s"), *HitResult.GetComponent()->GetName());	
		if(UStaticMeshComponent* ButtonMesh = Cast<UStaticMeshComponent>(HitResult.GetComponent()))
		{
			if(ButtonMesh->GetName().Equals("RightArrow"))
			{
				UE_LOG(LogTemp, Warning, TEXT("RightArrow"))	
			}
			else if(ButtonMesh->GetName().Equals("LeftArrow"))
			{
				UE_LOG(LogTemp, Warning, TEXT("LeftArrow"))	
			}
			else if(ButtonMesh->GetName().Equals("BuyButton"))
			{
				UE_LOG(LogTemp, Warning, TEXT("LeftArrow"))	
			}
		}
	}
}

void AShop::BeginPlay()
{
	Super::BeginPlay();

	Interactable = true;
}
