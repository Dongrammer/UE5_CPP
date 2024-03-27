#include "Notifies/WeaponComponent/AN_EndReload.h"

#include "Components/WeaponComponent.h"

void UAN_EndReload::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (WeaponComponent)
		WeaponComponent->bReload = false;
}
