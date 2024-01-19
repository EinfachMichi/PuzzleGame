#include "CropPlotActor.h"

#include "FarmingGameInstance.h"

ACropPlotActor::ACropPlotActor()
{
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneComponent"));
	DefaultSceneComponent->SetupAttachment(RootComponent);
	
	CropPlotMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CropPlotStaticMeshComponent"));
	CropPlotMesh->SetupAttachment(DefaultSceneComponent);
	
	CropMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CropStaticMeshComponent"));
	CropMesh->SetupAttachment(DefaultSceneComponent);
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxComponent->SetupAttachment(DefaultSceneComponent);
}

void ACropPlotActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateGrowthState(DeltaSeconds);
}

void ACropPlotActor::BeginPlay()
{
	Super::BeginPlay();

	Plantable = true;
	Harvestable = false;
}

void ACropPlotActor::UpdateGrowthState(float DeltaSeconds)
{
	if(!Occupied)
	{
		return;
	}
	
	if(GrowthState >= 1.f)
	{
		Harvestable = true;
		return;
	}

	GrowthState += GrowthRatePerMinute / 60 * DeltaSeconds;
	CropMesh->SetWorldScale3D(FVector::One() * GrowthState);
}

void ACropPlotActor::InInteractionRange()
{
	if(!CropMesh)
	{
		return;
	}

	if(Occupied)
	{
		if(GrowthState >= 1.f)
		{
			CropMesh->SetCustomDepthStencilValue(1);
		}
		else
		{
			CropMesh->SetCustomDepthStencilValue(2);
		}

		CropMesh->SetRenderCustomDepth(true);
	}
}

void ACropPlotActor::OutOfInteractionRange()
{
	if(!CropMesh)
	{
		return;
	}

	if(Occupied)
	{
		CropMesh->SetRenderCustomDepth(false);
	}
}

bool ACropPlotActor::Plant(ECropType NewCropType)
{
	if(Occupied || NewCropType == ECropType::None)
	{
		return false;
	}
	
	CropType = NewCropType;

	if(UFarmingGameInstance* GameInstance = Cast<UFarmingGameInstance>(GetWorld()->GetGameInstance()))
	{
		CropMesh->SetStaticMesh(GameInstance->GetSeedMesh(CropType));
		GrowthRatePerMinute = GameInstance->GetGrowthRate(CropType);
		GrowthState = DEFAULT_GROWTH_STATE;
		Occupied = true;
		Plantable = false;
		return true;
	}
	
	return false;
}

ECropType ACropPlotActor::Harvest()
{
	if(!Harvestable)
	{
		return ECropType::None;	
	}
	
	Occupied = false;
	Harvestable = false;
	CropMesh->SetStaticMesh(nullptr);
	Plantable = true;
	return CropType;
}

void ACropPlotActor::InPlantableRange(bool HasEnoughSeeds)
{
	if(!CropPlotMesh)
	{
		return;
	}

	if(!Occupied && Plantable && HasEnoughSeeds)
	{
		CropPlotMesh->SetCustomDepthStencilValue(1);
	}
	else
	{
		CropPlotMesh->SetCustomDepthStencilValue(2);
	}
	
	CropPlotMesh->SetRenderCustomDepth(true);
}

void ACropPlotActor::OutOfPlantableRange()
{
	if(!CropPlotMesh)
    {
    	return;
    }
	
	CropPlotMesh->SetRenderCustomDepth(false);
}
