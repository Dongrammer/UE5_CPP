#pragma once

#include "CoreMinimal.h"
#include "Actions/BaseAction.h"
#include "Act_Reload.generated.h"

UCLASS()
class UE5_CPP_API UAct_Reload : public UBaseAction
{
	GENERATED_BODY()
	
private:
	virtual void DoAction() override;

};
