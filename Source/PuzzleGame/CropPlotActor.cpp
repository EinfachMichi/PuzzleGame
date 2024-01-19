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
	
	// constexpr int32 NumEnumValues = static_cast<int32>(ECropType::Melon);
	// int32 RandomIndex = FMath::RandRange(0, NumEnumValues);
	//
	// const ECropType RandomSeedType =  static_cast<ECropType>(RandomIndex);
	// Plant(RandomSeedType);
}

void ACropPlotActor::UpdateGrowthState(float DeltaSeconds)
{
	if(GrowthState >= 1.f || !Occupied)
	{
		return;
	}

	GrowthState += GrowthRatePerMinute / 60 * DeltaSeconds;
	CropMesh->SetWorldScale3D(FVector::One() * GrowthState);
}

void ACropPlotActor::EnterInteractionState()
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

void ACropPlotActor::ExitInteractionState()
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
		GrowthState = DEFAULT_GROWTH_STAGE;
		Occupied = true;
		Plantable = false;
		return true;
	}
	
	return false;
}

ECropType ACropPlotActor::Harvest()
{
	if(GrowthState < 1.f)
	{
		return ECropType::None;	
	}
	
	Occupied = false;
	CropMesh->SetStaticMesh(nullptr);
	Plantable = true;
	return CropType;
}

void ACropPlotActor::EnterPlantableState(bool HasEnoughSeeds)
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

void ACropPlotActor::ExitPlantableState()
{
	if(!CropPlotMesh)
    {
    	return;
    }
	
	CropPlotMesh->SetRenderCustomDepth(false);
}
