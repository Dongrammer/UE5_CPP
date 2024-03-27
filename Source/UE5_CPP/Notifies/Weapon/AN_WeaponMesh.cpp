#include "Notifies/Weapon/AN_WeaponMesh.h"
#include "Weapons/BaseWeapon.h"

DEFINE_LOG_CATEGORY(CallWeaponFunctionByNameLog);

void UAN_WeaponMesh::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	Weapon = Cast<ABaseWeapon>(MeshComp->GetOwner());
}
