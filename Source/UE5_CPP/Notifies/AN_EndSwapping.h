#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_EndSwapping.generated.h"

UCLASS()
class UE5_CPP_API UAN_EndSwapping : public UAnimNotify
{
	GENERATED_BODY()
	
private:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
