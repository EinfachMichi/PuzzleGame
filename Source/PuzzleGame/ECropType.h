#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ECropType : uint8
{
	None UMETA(DisplayName = "None"),
	Carrot UMETA(DisplayName = "Carrot"),
	Pumpkin UMETA(DisplayName = "Pumpkin"),
	Melon UMETA(DisplayName = "Melon")
};

namespace ECrop_Loggable
{
	struct PUZZLEGAME_API FHelper
	{
		static const TCHAR* ToString(ECropType EnumValue);
	};
}