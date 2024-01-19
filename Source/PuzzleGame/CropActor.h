#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Engine/StaticMeshActor.h"
#include "CropActor.generated.h"

UCLASS()
class PUZZLEGAME_API ACropActor : public AStaticMeshActor, public IInteractable
{
	GENERATED_BODY()

private:
	UStaticMeshComponent* StaticMeshComponent;
	
protected:
	virtual void BeginPlay() override;
	
	virtual void Interact(APawn* Pawn) override;
	virtual void InInteractionRange() override;
	virtual void OutOfInteractionRange() override;

public:
	void SetStaticMesh(UStaticMesh* StaticMesh);
	
};
