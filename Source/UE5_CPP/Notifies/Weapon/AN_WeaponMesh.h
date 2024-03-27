#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_WeaponMesh.generated.h"

/**
 * MeshComp�� BaseWeapon���� �޾ƿ��� ���� �����ϰ� ���� ��Ƽ���� �θ��Դϴ�.
 * Weapon Mesh Animation���� ȣ���� �� ����Ͻñ� �ٶ��ϴ�.
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
