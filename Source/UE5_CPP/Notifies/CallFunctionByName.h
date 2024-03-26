#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CallFunctionByName.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(CallFunctionByNameLog, Log, All);

UCLASS()
class UE5_CPP_API UCallFunctionByName : public UAnimNotify
{
	GENERATED_BODY()
	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
	UPROPERTY(EditInstanceOnly, meta = (AllowPrivateAccess = "true"))
	FName FunctionName;
};
