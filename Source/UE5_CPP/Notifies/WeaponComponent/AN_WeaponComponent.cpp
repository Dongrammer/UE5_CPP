#include "Notifies/WeaponComponent/AN_WeaponComponent.h"

#include "Characters/BaseCharacter.h"

DEFINE_LOG_CATEGORY(AN_WeaponCompLog);

void UAN_WeaponComponent::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	Owner = Cast<ABaseCharacter>(MeshComp->GetOwner());

	if (Owner)
		WeaponComponent = Owner->GetWeaponComponent();
}
