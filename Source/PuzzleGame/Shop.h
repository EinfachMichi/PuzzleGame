#pragma once

#include "CoreMinimal.h"
#include "EItemType.h"
#include "FShopItemInfo.h"
#include "ShopButton.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"
#include "Shop.generated.h"

UCLASS()
class PUZZLEGAME_API AShop : public AActor
{
	GENERATED_BODY()
	
	int CurrentItemIndex;
	void UpdateItem();
	
public:	
	AShop();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Buttons")
	AShopButton* RightArrowButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Buttons")
	AShopButton* LeftArrowButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Buttons")
	AShopButton* BuyButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Shop")
	TMap<EItemType, FShopItemInfo> ShopInfos;

	UPROPERTY(EditAnywhere, Category="Display")
	TArray<UStaticMesh*> NumberMeshes;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
    USceneComponent* DefaultSceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* ItemMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	USceneComponent* DropPosition;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* FirstMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* SecondMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* ThirdMesh;

	UPROPERTY(EditAnywhere, Category="Shop")
	USoundCue* BoughtSoundCue;
	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category="Shop")
	void CycleThroughItems(float Direction);

	UFUNCTION(BlueprintCallable, Category="Shop")
	void BuyItem(APawn* Pawn);
	
};
