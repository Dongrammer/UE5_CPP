#pragma once

#include "CoreMinimal.h"
#include "Actions/BaseAction.h"
#include "Act_Aiming.generated.h"

UCLASS()
class UE5_CPP_API UAct_Aiming : public UBaseAction
{
	GENERATED_BODY()
	
public:
	virtual void DoAction() override;
	virtual void TickAction() override;
	virtual void EndAction() override;
};
