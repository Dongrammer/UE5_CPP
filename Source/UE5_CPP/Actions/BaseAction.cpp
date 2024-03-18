#include "Actions/BaseAction.h"

#include "Characters/BaseCharacter.h"
#include "Weapons/BaseWeapon.h"
#include "ActionEnum.h"

void UBaseAction::SetOwner(ABaseCharacter* InOwner)
{
	Owner = InOwner;
}

void UBaseAction::ExecuteAction(const EActionTiming Timing)
{
	switch (Timing)
	{
	case EActionTiming::Do :
		DoAction(); break;
	case EActionTiming::Tick :
		TickAction(); break;
	case EActionTiming::End :
		EndAction(); break;
	}
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
