#pragma once

#include "CoreMinimal.h"
#include "Actions/BaseAction.h"
#include "Act_Fire.generated.h"

UCLASS()
class UE5_CPP_API UAct_Fire : public UBaseAction
{
	GENERATED_BODY()
	
public:
	virtual void DoAction() override;
	virtual void EndAction() override;
};
