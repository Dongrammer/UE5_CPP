#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputDataAsset.generated.h"

class UInputAction;

UCLASS()
class UE5_CPP_API UInputDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Motion", meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Motion", meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	
	/* ==================================================================================================== */

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Select", meta = (AllowPrivateAccess = "true"))
	UInputAction* MainWeaponSelect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Select", meta = (AllowPrivateAccess = "true"))
	UInputAction* SecondaryWeaponSelect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Select", meta = (AllowPrivateAccess = "true"))
	UInputAction* ThrowableWeaponSelect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Select", meta = (AllowPrivateAccess = "true"))
	UInputAction* ScrollWeaponSelect;

	/* ==================================================================================================== */

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Motion", meta = (AllowPrivateAccess = "true"))
	UInputAction* AvoidAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Actions", meta = (AllowPrivateAccess = "true"))
	UInputAction* MainAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Actions", meta = (AllowPrivateAccess = "true"))
	UInputAction* SubAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Actions", meta = (AllowPrivateAccess = "true"))
	UInputAction* ReloadAction;
};
