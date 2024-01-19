#include "ECropType.h"

namespace ECrop_Loggable
{
	const TCHAR* FHelper::ToString(ECropType EnumValue)
	{
		switch (EnumValue)
		{
		case ECropType::None: return TEXT("None");
		case ECropType::Carrot: return TEXT("Carrot");
		case ECropType::Pumpkin: return TEXT("Pumpkin");
		case ECropType::Melon: return TEXT("Melon");
		default: return TEXT("Invalid");
		}
	}
}