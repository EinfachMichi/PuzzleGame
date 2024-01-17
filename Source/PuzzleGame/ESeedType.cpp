#include "ESeedType.h"

namespace ESeedType_Loggable
{
	const TCHAR* FHelper::ToString(ESeedType EnumValue)
	{
		switch (EnumValue)
		{
		case ESeedType::Carrot: return TEXT("Carrot");
		case ESeedType::Pumpkin: return TEXT("Pumpkin");
		case ESeedType::Melon: return TEXT("Melon");
		default: return TEXT("Invalid");
		}
	}
}