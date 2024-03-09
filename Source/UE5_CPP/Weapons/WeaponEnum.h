#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EWeaponSlot : uint8
{
	E_None UMETA(Hidden),
	E_Main UMETA(DisplayName = "Main"),
	E_Second UMETA(DisplayName = "Second"),
	E_Throwable UMETA(DisplayName = "Throwable"),
	E_Max
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	E_None UMETA(Hidden),
	E_RIfle UMETA(DisplayName = "Rifle"),
	E_Pistol UMETA(DisplayName = "Pistol"),
	E_Throwable UMETA(DisplayName = "Throwable"),
	E_Max
};

UENUM(BlueprintType)
enum class EAttachType : uint8
{
	E_Holder UMETA(DisplayName = "Holder"),
	E_Handle UMETA(DisplayName = "Handle"),
	E_Max
};