#pragma once

#include "CoreMinimal.h"
#include "Notifies/WeaponComponent/AN_WeaponComponent.h"
#include "AN_SetWeaponState.generated.h"

enum class EWeaponState : uint8;
/**
 * Weapon Component를 통해서 무기의 상태를 설정해주는 노티파이입니다.
 * 상태값이 바뀜에 따라서 애니메이션이 바뀐다는 점을 유의하셔야 합니다.
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
