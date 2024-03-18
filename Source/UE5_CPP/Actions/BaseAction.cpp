#include "Actions/BaseAction.h"

#include "Characters/BaseCharacter.h"
#include "Weapons/BaseWeapon.h"

void UBaseAction::SetOwner(ABaseCharacter* InOwner)
{
	Owner = InOwner;
}

void UBaseAction::DoAction()
{
}

void UBaseAction::TickAction()
{
}

void UBaseAction::EndAction()
{
}
