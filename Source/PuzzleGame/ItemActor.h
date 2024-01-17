#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Engine/StaticMeshActor.h"
#include "ItemActor.generated.h"

UCLASS()
class PUZZLEGAME_API AItemActor : public AStaticMeshActor, public IInteractable
{
	GENERATED_BODY()

public:
	UStaticMeshComponent* MeshComponent;
	
public:
	virtual void Interact() override;
	virtual void SetInteractable(bool Interactable) override;

private:
	void Initialize();
	
protected:
	virtual void BeginPlay() override;
};
