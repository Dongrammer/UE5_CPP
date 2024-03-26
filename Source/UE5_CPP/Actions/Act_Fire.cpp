#include "Actions/Act_Fire.h"

#include "Characters/BaseCharacter.h"
#include "Components/WeaponComponent.h"
#include "Weapons/BaseWeapon.h"

DEFINE_LOG_CATEGORY(ActionLog);

void UAct_Fire::DoAction()
{
	Super::DoAction();

	if (ABaseWeapon* Weapon = Owner->GetWeaponComponent()->GetCurrentWeapon())
		Weapon->Fire();
}

void UAct_Fire::EndAction()
{
	Super::EndAction();

	if (ABaseWeapon* Weapon = Owner->GetWeaponComponent()->GetCurrentWeapon())
		Weapon->HoldFire();
}
