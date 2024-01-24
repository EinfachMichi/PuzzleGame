#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Carrot UMETA(DisplayName = "Carrot"),
	Pumpkin UMETA(DisplayName = "Pumpkin"),
	Melon UMETA(DisplayName = "Melon"),
	Crate UMETA(DisplayName = "Crate")
};