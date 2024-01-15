#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUZZLEGAME_API UPlayerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPlayerComponent();
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Line Trace")
	float LineTraceDistance;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	FHitResult LineTrace();
};