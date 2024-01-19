#pragma once

#include "CoreMinimal.h"
#include "ECropType.h"
#include "ItemActor.h"
#include "SeedBagActor.generated.h"

UCLASS()
class PUZZLEGAME_API ASeedBagActor : public AItemActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Info")
	ECropType CropType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Info")
	int SeedCount;

	virtual void Interact(APawn* ) override;

protected:
	virtual void BeginPlay() override;
};
