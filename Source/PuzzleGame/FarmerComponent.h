#pragma once

#include "CoreMinimal.h"
#include "ESeedType.h"
#include "Components/ActorComponent.h"
#include "FarmerComponent.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBuildModeChanged);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUZZLEGAME_API UFarmerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Debug")
	bool LogSeedInventory;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Seeds")
	TMap<ESeedType, int32> SeedInventory;

	UPROPERTY(BlueprintAssignable, Category="Building")
	FBuildModeChanged BuildModeChanged;

	UPROPERTY(BlueprintReadOnly, Category="Building")
	bool BuildMode;

private:
	ESeedType CurrentSeedType;
	
public:	
	UFarmerComponent();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddSeeds(ESeedType SeedType, int32 SeedCount);

	UFUNCTION(BlueprintCallable, Category="Building")
	void ToggleBuildMode();

	UFUNCTION(BlueprintCallable, Category="Building")
	void SetSeedType(ESeedType NewSeedType);

private:
	// This method is called in tick
	void ManageBuildMode();
	
protected:
	virtual void BeginPlay() override;

};
