#pragma once

#include "CoreMinimal.h"
#include "Notifies/WeaponComponent/AN_WeaponComponent.h"
#include "AN_WeaponComp_CallWeaponFunction.generated.h"

/**
 * BaseCharacter�� ��ӹ��� ĳ���� Ŭ������ ����ϴ� ��Ƽ�����Դϴ�.
 * WeaponComponent�� ���ؼ� Weapon Ŭ������ �Լ��� ȣ���մϴ�.
 */
UCLASS()
class UE5_CPP_API UAN_WeaponComp_CallWeaponFunction : public UAN_WeaponComponent
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
