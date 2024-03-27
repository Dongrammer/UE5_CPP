#include "Animations/Rifle_AnimInstance.h"

#include "Weapons/WeaponEnum.h"
#include "Weapons/Guns/AssaultRifle.h"

void URifle_AnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Weapon = Cast<AAssaultRifle>(TryGetPawnOwner());
}

void URifle_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Weapon == nullptr) return;

	WeaponState = Weapon->WeaponState;
	bReload = Weapon->bReload;
}
