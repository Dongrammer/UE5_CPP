#pragma once

#include "CoreMinimal.h"
#include "Notifies/WeaponComponent/AN_WeaponComponent.h"
#include "AN_EndReload.generated.h"

UCLASS()
class UE5_CPP_API UAN_EndReload : public UAN_WeaponComponent
{
	GENERATED_BODY()

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
