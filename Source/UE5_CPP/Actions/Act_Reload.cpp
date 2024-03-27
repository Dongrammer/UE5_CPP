#include "Actions/Act_Reload.h"

#include "Characters/BaseCharacter.h"
#include "Weapons/BaseWeapon.h"
#include "Components/WeaponComponent.h"
#include "Weapons/WeaponEnum.h"

void UAct_Reload::DoAction()
{
	Super::DoAction();

	if (Owner->GetWeaponComponent()->GetCurrentWeapon()->IsFullRound()) return;

	Owner->GetWeaponComponent()->bReload = true;
	Owner->GetWeaponComponent()->GetCurrentWeapon()->bReload = true;
	Owner->GetWeaponComponent()->GetCurrentWeapon()->WeaponState = EWeaponState::Reload;
}
