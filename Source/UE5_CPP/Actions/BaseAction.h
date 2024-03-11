#pragma once

#include "CoreMinimal.h"

class ABaseCharacter;
class ABaseWeapon;

class UE5_CPP_API BaseAction
{
public:
	void SetOwner(ABaseCharacter* InOwner);

	virtual void DoAction();

private:
	ABaseCharacter* Owner;

};
