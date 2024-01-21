#include "CropPlot.h"

#include "Crop.h"
#include "FarmingGameMode.h"
#include "Kismet/GameplayStatics.h"

ACropPlot::ACropPlot()
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

void ACropPlot::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateGrowthState(DeltaSeconds);
}

void ACropPlot::BeginPlay()
{
	Super::BeginPlay();

	NiagaraHarvestEffect = FindComponentByTag<UActorComponent>("Effect");
}

void ACropPlot::UpdateGrowthState(float DeltaSeconds)
{
	if(!Occupied)
	{
		return;
	}
	
	if(IsHarvestable())
	{
		return;
	}

	GrowthState += GrowthRatePerMinute / 60 * DeltaSeconds;
	CropMesh->SetWorldScale3D(FVector::One() * GrowthState);
}

void ACropPlot::EnableOutline()
{
	if(!CropMesh)
	{
		return;
	}
	
	if(Occupied)
	{
		if(IsHarvestable())
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

void ACropPlot::DisableOutline()
{
	if(!CropMesh)
	{
		return;
	}

	CropMesh->SetRenderCustomDepth(false);
}

void ACropPlot::ShowInteraction()
{
	EnableOutline();
}

void ACropPlot::HideInteraction()
{
	DisableOutline();
}

bool ACropPlot::Plant(ECropType NewCropType)
{
	if(Occupied || NewCropType == ECropType::None)
	{
		return false;
	}
	
	CropType = NewCropType;

	if(AFarmingGameMode* GameMode = Cast<AFarmingGameMode>(GetWorld()->GetAuthGameMode()))
	{
		CropMesh->SetStaticMesh(GameMode->GetSeedMesh(CropType));
		GrowthRatePerMinute = GameMode->GetGrowthRate(CropType);
		GrowthState = DEFAULT_GROWTH_STATE;
		CropMass = GameMode->GetMass(CropType);
		Occupied = true;
		return true;
	}
	return false;
}

ACrop* ACropPlot::Harvest()
{
	if(!IsHarvestable())
	{
		return nullptr;	
	}

	FVector CropActorLocation = GetActorLocation() + CropMesh->GetRelativeLocation();
	FRotator CropActorRotation = GetActorRotation() + CropMesh->GetRelativeRotation();
	AActor* CropActor = GetWorld()->SpawnActor<AActor>(ACrop::StaticClass(), CropActorLocation, CropActorRotation);

	ACrop* Crop = Cast<ACrop>(CropActor);
	Crop->SetCropType(CropType);
	Crop->SetStaticMesh(CropMesh->GetStaticMesh());
	Crop->SetMass(CropMass);
	
	Occupied = false;
	CropMesh->SetStaticMesh(nullptr);

	if(NiagaraHarvestEffect)
	{
		NiagaraHarvestEffect->Activate(true);
	}
	
	if(Crop->IsBig())
	{
		UGameplayStatics::PlaySoundAtLocation(this, BigCropSoundCue, GetActorLocation());
	}
	else
	{
		UGameplayStatics::PlaySoundAtLocation(this, SmallCropSoundCue, GetActorLocation());
	}

	OnCropHarvest.Broadcast();
	return Crop;
}

void ACropPlot::UpdatePlantableVisuels(bool Enabled, bool Requirement)
{
	CropPlotMesh->SetRenderCustomDepth(Enabled);
	
	if(Requirement && !Occupied)
	{
		CropPlotMesh->SetCustomDepthStencilValue(1);
	}
	else
	{
		CropPlotMesh->SetCustomDepthStencilValue(2);
	}
}

bool ACropPlot::IsHarvestable()
{
	if(GrowthState >= 1.f && Occupied)
	{
		return true;
	}
	return false;
}
