#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_WeaponComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(AN_WeaponCompLog, Log, All);

class UWeaponComponent;
class ABaseCharacter;

UCLASS()
class UE5_CPP_API UAN_WeaponComponent : public UAnimNotify
{
	GENERATED_BODY()

protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

protected:
	UPROPERTY()
	ABaseCharacter* Owner;
	UPROPERTY()
	UWeaponComponent* WeaponComponent;
};
