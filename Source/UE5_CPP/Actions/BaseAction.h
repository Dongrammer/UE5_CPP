#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseAction.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(ActionLog, Log, All);

class ABaseCharacter;
class ABaseWeapon;

UCLASS()
class UE5_CPP_API UBaseAction : public UObject
{
	GENERATED_BODY()
	
public:
	void SetOwner(ABaseCharacter* InOwner);
	virtual void DoAction();
	virtual void TickAction();
	virtual void EndAction();

protected:
	ABaseCharacter* Owner;
};