#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_WeaponMesh.generated.h"

/**
 * MeshComp가 BaseWeapon에서 받아오는 것을 상정하고 만든 노티파이 부모입니다.
 * Weapon Mesh Animation에서 호출할 때 사용하시기 바랍니다.
 */

class ABaseWeapon;

DECLARE_LOG_CATEGORY_EXTERN(CallWeaponFunctionByNameLog, Log, All);

UCLASS()
class UE5_CPP_API UAN_WeaponMesh : public UAnimNotify
{
	GENERATED_BODY()
	
protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

protected:
	UPROPERTY()
	ABaseWeapon* Weapon;
};
