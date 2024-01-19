#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "ItemActor.generated.h"

UCLASS()
class PUZZLEGAME_API AItemActor : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	UStaticMeshComponent* MeshComponent;
	
protected:
	virtual void BeginPlay() override;
};
