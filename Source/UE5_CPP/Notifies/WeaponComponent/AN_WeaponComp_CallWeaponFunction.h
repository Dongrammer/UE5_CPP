#pragma once

#include "CoreMinimal.h"
#include "Notifies/WeaponComponent/AN_WeaponComponent.h"
#include "AN_WeaponComp_CallWeaponFunction.generated.h"

/**
 * BaseCharacter를 상속받은 캐릭터 클래스가 사용하는 노티파이입니다.
 * WeaponComponent를 통해서 Weapon 클래스의 함수를 호출합니다.
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
