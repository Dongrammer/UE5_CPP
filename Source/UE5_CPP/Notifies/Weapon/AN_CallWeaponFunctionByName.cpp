#include "Notifies/Weapon/AN_CallWeaponFunctionByName.h"
#include "Weapons/BaseWeapon.h"

void UAN_CallWeaponFunctionByName::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (Weapon)
	{
		if (UFunction* FunctionPtr = Weapon->FindFunction(FunctionName))
			Weapon->ProcessEvent(FunctionPtr, nullptr);
		else
			UE_LOG(CallWeaponFunctionByNameLog, Warning, L"%s Function Name is Wrong! Check Function Name!", *FunctionName.ToString());
	}
}

FString UAN_CallWeaponFunctionByName::GetNotifyName_Implementation() const
{
	if (FunctionName != "None")	// FunctionName의 기본값은 None
		return "Call " + FunctionName.ToString();

	return Super::GetNotifyName_Implementation();
}
