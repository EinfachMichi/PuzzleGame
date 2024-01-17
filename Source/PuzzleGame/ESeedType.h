#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ESeedType : uint8
{
	Carrot UMETA(DisplayName = "Carrot"),
	Pumpkin UMETA(DisplayName = "Pumpkin"),
	Melon UMETA(DisplayName = "Melon")
};

namespace ESeedType_Loggable
{
	struct PUZZLEGAME_API FHelper
	{
		static const TCHAR* ToString(ESeedType EnumValue);
	};
}