#pragma once

#include "CoreMinimal.h"
#include "ECropType.h"
#include "PlayerComponent.h"
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
	bool LogCropSeedInventory;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Crops")
	TMap<ECropType, int32> CropSeedInventory;

	UPROPERTY(BlueprintAssignable, Category="Building")
	FBuildModeChanged BuildModeChanged;

	UPROPERTY(BlueprintReadOnly, Category="Building")
	bool BuildMode;

private:
	ECropType CurrentCropType;
	UPlayerComponent* PlayerComponent;
	AActor* CurrentLineTraceActor;
	AActor* OldLineTraceActor;
	
public:	
	UFarmerComponent();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddSeeds(ECropType CropType, int32 SeedCount);

	UFUNCTION(BlueprintCallable, Category="Building")
	void ToggleBuildMode();

	UFUNCTION(BlueprintCallable, Category="Building")
	void SetSeedType(ECropType NewCropType);

private:
	// This method is called in tick
	void ManageBuildMode();
	void Initialize();
	
protected:
	virtual void BeginPlay() override;

};
