#include "SeedBag.h"

ASeedBag::ASeedBag()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASeedBag::BeginPlay()
{
	Super::BeginPlay();
}

ESeedType ASeedBag::GetSeedType()
{
	return SeedType;
}