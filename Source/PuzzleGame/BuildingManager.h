#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuildingManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUZZLEGAME_API UBuildingManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBuildingManager();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;
};
