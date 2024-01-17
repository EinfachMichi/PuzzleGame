#include "CropSpot.h"

ACropSpot::ACropSpot()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACropSpot::BeginPlay()
{
	Super::BeginPlay();
}

void ACropSpot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACropSpot::SetCrop(ACrop* Crop)
{
	this->CurrentCrop = Crop;
}

bool ACropSpot::IsOccupied() const
{
	if(CurrentCrop)
	{
		return true;
	}
	return false;
}
