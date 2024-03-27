#include "Notifies/WeaponComponent/AN_SetWeaponState.h"

#include "Components/WeaponComponent.h"
#include "Weapons/BaseWeapon.h"

void UAN_SetWeaponState::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (WeaponComponent)
		WeaponComponent->GetCurrentWeapon()->WeaponState = WeaponState;
}

FString UAN_SetWeaponState::GetNotifyName_Implementation() const
{
	return "Set " + UEnum::GetValueAsString(WeaponState).Replace(L"EWeaponState::", L"Weapon ");
	// UEnum::GetValueAsString �� ��� �� : EWeaponState::Idle
	// Replace�� ����Ͽ� ���� ���� ǥ��
}
