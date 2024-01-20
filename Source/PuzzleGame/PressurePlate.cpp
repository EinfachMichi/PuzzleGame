#include "PressurePlate.h"
#include "Crop.h"

APressurePlate::APressurePlate()
{
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneComponent"));
	DefaultSceneComponent->SetupAttachment(RootComponent);

	SignSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Sign"));
	SignSceneComponent->SetupAttachment(DefaultSceneComponent);
	
	DisplaySceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Display"));
	DisplaySceneComponent->SetupAttachment(SignSceneComponent);
	
	FirstMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("First"));
	FirstMesh->SetupAttachment(DisplaySceneComponent);
	
	SecondMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Second"));
	SecondMesh->SetupAttachment(DisplaySceneComponent);
	
	ThirdMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Third"));
	ThirdMesh->SetupAttachment(DisplaySceneComponent);
	
	PressurePlateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PressurePlateStaticMeshComponent"));
	PressurePlateMesh->SetupAttachment(DefaultSceneComponent);
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollisionComponent"));
	BoxComponent->SetupAttachment(DefaultSceneComponent);
}

float APressurePlate::GetMass()
{
	if(!BoxComponent)
	{
		return -1;
	}
	
	TArray<AActor*> OverlappingActors;
	BoxComponent->GetOverlappingActors(OverlappingActors);

	float Mass = 0;
	for (AActor* Actor : OverlappingActors)
	{
		if(ACrop* Crop = Cast<ACrop>(Actor))
		{
			Mass += Crop->GetMass();
		}
	}
	return Mass;
}

void APressurePlate::UpdateDisplay()
{
	int Mass = GetMass();
	
	for (int i = 0; i < 3; i++)
	{
		if(Mass < 0)
		{
			return;
		}
		
		int Digit = Mass % 10;
		Mass /= 10;
		
		ChangeMesh(i, Digit);
	}
}

void APressurePlate::ChangeMesh(int Mesh, int Number)
{
	switch (Mesh)
	{
	case 0:
		ThirdMesh->SetStaticMesh(NumberMeshes[Number]);
		break;
	case 1:
		SecondMesh->SetStaticMesh(NumberMeshes[Number]);
		break;
	case 2:
		FirstMesh->SetStaticMesh(NumberMeshes[Number]);
		break;
	}
}
