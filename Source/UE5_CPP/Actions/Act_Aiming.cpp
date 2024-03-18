#include "Actions/Act_Aiming.h"

#include "Characters/BaseCharacter.h"
#include "Components/WeaponComponent.h"

void UAct_Aiming::DoAction()
{
	Super::DoAction();

	Owner->GetWeaponComponent()->SetAiming(true);
	Owner->bUseControllerRotationYaw = true;
}

void UAct_Aiming::TickAction()
{
	Super::TickAction();
}

void UAct_Aiming::EndAction()
{
	Super::EndAction();

	Owner->GetWeaponComponent()->SetAiming(false);
	Owner->bUseControllerRotationYaw = false;
}
