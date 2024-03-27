#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Rifle_AnimInstance.generated.h"

enum class EWeaponState : uint8;
class AAssaultRifle;

UCLASS()
class UE5_CPP_API URifle_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowprivateAccess = "true"))
	EWeaponState WeaponState;

	UPROPERTY()
	AAssaultRifle* Weapon;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bReload = false;
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
