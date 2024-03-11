#include "Actions/BaseAction.h"

#include "Characters/BaseCharacter.h"
#include "Weapons/BaseWeapon.h"

void BaseAction::SetOwner(ABaseCharacter* InOwner)
{
	Owner = InOwner;

}

void BaseAction::DoAction()
{
}
