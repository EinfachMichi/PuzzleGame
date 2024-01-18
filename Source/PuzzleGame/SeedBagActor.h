#pragma once

#include "CoreMinimal.h"
#include "ESeedType.h"
#include "ItemActor.h"
#include "SeedBagActor.generated.h"

UCLASS()
class PUZZLEGAME_API ASeedBagActor : public AItemActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Info")
	ESeedType SeedType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Info")
	int SeedCount;

	virtual void Interact() override;

protected:
	virtual void BeginPlay() override;
};
