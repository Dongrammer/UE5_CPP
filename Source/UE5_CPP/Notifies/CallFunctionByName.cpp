#include "Notifies/CallFunctionByName.h"

#include "Weapons/BaseWeapon.h"

DEFINE_LOG_CATEGORY(CallFunctionByNameLog);

void UCallFunctionByName::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (ABaseWeapon* Weapon = Cast<ABaseWeapon>(MeshComp->GetOwner()))
	{
		if (UFunction* Function = Weapon->FindFunction(FunctionName))
			Weapon->ProcessEvent(Function, nullptr);
		else
			UE_LOG(CallFunctionByNameLog, Warning, L"\"%s\" Functinon Can\'t Find! Check Name", *FunctionName.ToString());
	}
}
