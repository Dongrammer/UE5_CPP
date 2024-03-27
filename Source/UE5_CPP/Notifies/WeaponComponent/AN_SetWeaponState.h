#pragma once

#include "CoreMinimal.h"
#include "Notifies/WeaponComponent/AN_WeaponComponent.h"
#include "AN_SetWeaponState.generated.h"

enum class EWeaponState : uint8;
/**
 * Weapon Component�� ���ؼ� ������ ���¸� �������ִ� ��Ƽ�����Դϴ�.
 * ���°��� �ٲ� ���� �ִϸ��̼��� �ٲ�ٴ� ���� �����ϼž� �մϴ�.
 */
UCLASS()
class UE5_CPP_API UAN_SetWeaponState : public UAN_WeaponComponent
{
	GENERATED_BODY()

private:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

public:
	virtual FString GetNotifyName_Implementation() const override;

private:
	UPROPERTY(EditInstanceOnly, meta = (AllowPrivateAccess = "true"))
	EWeaponState WeaponState;
};
