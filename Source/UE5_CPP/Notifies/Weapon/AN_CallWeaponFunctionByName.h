#pragma once

#include "CoreMinimal.h"
#include "Notifies/Weapon/AN_WeaponMesh.h"
#include "AN_CallWeaponFunctionByName.generated.h"

/**
 * �Լ� �̸����� BaseWeapon�� �ִ� �Լ��� ȣ�����ִ� ������ �ϴ� ��Ƽ�����Դϴ�.
 */
UCLASS()
class UE5_CPP_API UAN_CallWeaponFunctionByName : public UAN_WeaponMesh
{
	GENERATED_BODY()
	
private:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

public:
	virtual FString GetNotifyName_Implementation() const override;

private:
	UPROPERTY(EditInstanceOnly, meta = (AllowPrivateAccess = "true"))
	FName FunctionName;
};
