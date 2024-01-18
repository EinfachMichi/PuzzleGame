#include "CropPlotActor.h"

#include "FarmingGameInstance.h"

ACropPlotActor::ACropPlotActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CropPlotMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CropPlotStaticMeshComponent"));
	CropPlotMesh->SetupAttachment(RootComponent);
	
	CropMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CropStaticMeshComponent"));
	CropMesh->SetupAttachment(CropPlotMesh);
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxComponent->SetupAttachment(CropPlotMesh);
}

void ACropPlotActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateGrowthState(DeltaSeconds);
}

void ACropPlotActor::BeginPlay()
{
	Super::BeginPlay();
	
	constexpr int32 NumEnumValues = static_cast<int32>(ESeedType::Melon);
	int32 RandomIndex = FMath::RandRange(0, NumEnumValues);

	const ESeedType RandomSeedType =  static_cast<ESeedType>(RandomIndex);
	PlantCrop(RandomSeedType);
}

bool ACropPlotActor::IsOccupied() const
{
	return Occupied;
}

void ACropPlotActor::PlantCrop(ESeedType CropSeedType)
{
	if(Occupied)
	{
		return;
	}
	
	SeedType = CropSeedType;

	if(UFarmingGameInstance* GameInstance = Cast<UFarmingGameInstance>(GetWorld()->GetGameInstance()))
	{
		CropMesh->SetStaticMesh(GameInstance->GetSeedMesh(SeedType));
		GrowthState = DEFAULT_GROWTH_STAGE;
		Occupied = true;
	}
}

bool ACropPlotActor::HarvestCrop(OUT ESeedType OldSeedType)
{
	if(GrowthState >= 1.f)
	{
		return false;
	}
	
	Occupied = false;
	OldSeedType = SeedType;
	return true;
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