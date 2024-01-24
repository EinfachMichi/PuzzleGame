#include "Shop.h"

#include "PlayerComponent.h"
#include "SeedBagActor.h"
#include "Kismet/GameplayStatics.h"

AShop::AShop()
{
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneComponent"));
	DefaultSceneComponent->SetupAttachment(RootComponent);

	DropPosition = CreateDefaultSubobject<USceneComponent>(TEXT("DropPosition"));
	DropPosition->SetupAttachment(DefaultSceneComponent);
	
	FirstMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("First"));
	FirstMesh->SetupAttachment(DefaultSceneComponent);
	
	SecondMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Second"));
	SecondMesh->SetupAttachment(DefaultSceneComponent);
	
	ThirdMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Third"));
	ThirdMesh->SetupAttachment(DefaultSceneComponent);

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetupAttachment(DefaultSceneComponent);
}

void AShop::BeginPlay()
{
	Super::BeginPlay();

	CurrentItemIndex = ShopInfos.Num() - 1;
	UpdateItem();
}

void AShop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShop::CycleThroughItems(float Direction)
{
	CurrentItemIndex += Direction * -1;

	UpdateItem();
}

void AShop::UpdateItem()
{
	if(!ItemMesh || ShopInfos.Num() == 0)
	{
		return;
	}
	
	TArray<EItemType> ShopItems;
	ShopInfos.GetKeys(ShopItems);

	if(ShopItems.Num() == 0)
	{
		return;
	}
	
	if(ShopItems.Num() <= CurrentItemIndex)
	{
		CurrentItemIndex = 0;
	}

	if(CurrentItemIndex < 0)
	{
		CurrentItemIndex = ShopItems.Num() - 1;
	}

	ItemMesh->SetStaticMesh(ShopInfos[ShopItems[CurrentItemIndex]].ItemMesh);

	int Price = ShopInfos[ShopItems[CurrentItemIndex]].Price;
	
	for (int i = 0; i < 3; i++)
	{
		if(Price < 0)
		{
			return;
		}
		
		int Digit = Price % 10;
		Price /= 10;
		
		switch (i)
		{
		case 0:
			ThirdMesh->SetStaticMesh(NumberMeshes[Digit]);
			break;
		case 1:
			SecondMesh->SetStaticMesh(NumberMeshes[Digit]);
			break;
		case 2:
			FirstMesh->SetStaticMesh(NumberMeshes[Digit]);
			break;
		}
	}
}

void AShop::BuyItem(APawn* Pawn)
{
	TArray<EItemType> ShopItems;
	ShopInfos.GetKeys(ShopItems);
	
	if(UPlayerComponent* PlayerComponent = Pawn->FindComponentByClass<UPlayerComponent>())
	{
		FShopItemInfo ShopItemInfo = ShopInfos[ShopItems[CurrentItemIndex]];
		if(PlayerComponent->GetCurrency() >= ShopItemInfo.Price)
		{
			PlayerComponent->RemoveCurrency(ShopItemInfo.Price);
			AActor* Actor = GetWorld()->SpawnActor<AActor>(ShopItemInfo.ItemActor->GeneratedClass,
				DropPosition->GetComponentLocation(), DropPosition->GetComponentRotation());

			if(ASeedBagActor* SeedBagActor = Cast<ASeedBagActor>(Actor))
			{
				SeedBagActor->SetCropType(ShopItemInfo.CropType);
			}

			if(AItemActor* ItemActor = Cast<AItemActor>(Actor))
			{
				ItemActor->GetMesh()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
			}
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), BoughtSoundCue, GetActorLocation());
		}
	}
}