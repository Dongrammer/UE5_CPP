#include "Notifies/AN_EndSwapping.h"

#include "Characters/BaseCharacter.h"
#include "Components/WeaponComponent.h"

void UAN_EndSwapping::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ABaseCharacter* Owner = Cast<ABaseCharacter>(MeshComp->GetOwner());
	Owner->GetWeaponComponent()->bSwapping = false;
}
