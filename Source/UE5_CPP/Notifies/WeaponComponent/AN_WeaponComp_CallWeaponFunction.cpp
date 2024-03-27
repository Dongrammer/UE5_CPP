#include "Notifies/WeaponComponent/AN_WeaponComp_CallWeaponFunction.h"

#include "Components/WeaponComponent.h"
#include "Weapons/BaseWeapon.h"

void UAN_WeaponComp_CallWeaponFunction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (WeaponComponent)
	{
		ABaseWeapon* Weapon = WeaponComponent->GetCurrentWeapon();

		if (UFunction* FunctionPtr = Weapon->FindFunction(FunctionName))
			Weapon->ProcessEvent(FunctionPtr, nullptr);
		else
			UE_LOG(AN_WeaponCompLog, Warning, L"%s Function Name is Wrong! Check Function Name!", *FunctionName.ToString());
	}
}

FString UAN_WeaponComp_CallWeaponFunction::GetNotifyName_Implementation() const
{
	if (FunctionName != "None")	// FunctionName의 기본값은 None
		return "Call " + FunctionName.ToString();

	return Super::GetNotifyName_Implementation();
}
