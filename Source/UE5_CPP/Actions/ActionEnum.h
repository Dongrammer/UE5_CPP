#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType, meta = (Bitflags))
enum class EActionType : uint8
{
	None UMETA(Hidden),
	MainAction UMETA(DisplayName = "Main Action"),
	SubAction UMETA(DisplayName = "Sub Action"),
	AvoidAction UMETA(DisplayName = "Avoid Action"),
	ReloadAction UMETA(DisplayName = "Reload Action"),
	Max UMETA(Hidden)
};