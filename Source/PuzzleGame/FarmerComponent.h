#pragma once

#include "CoreMinimal.h"
#include "ESeedType.h"
#include "Components/ActorComponent.h"
#include "FarmerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUZZLEGAME_API UFarmerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Debug")
	bool LogSeedInventory;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Seeds")
	TMap<ESeedType, int32> SeedInventory;
	
public:	
	UFarmerComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddSeeds(ESeedType SeedType, int32 SeedCount);

protected:
	virtual void BeginPlay() override;

};
