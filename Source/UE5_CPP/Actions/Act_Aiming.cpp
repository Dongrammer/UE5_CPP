#include "Actions/Act_Aiming.h"

#include "Characters/BaseCharacter.h"
#include "Components/WeaponComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UAct_Aiming::DoAction()
{
	Super::DoAction();

	Owner->GetWeaponComponent()->SetAiming(true);
	Owner->bUseControllerRotationYaw = true;
}

void UAct_Aiming::TickAction()
{
	Super::TickAction();

	if (bIsClick == false) return;

	// 움직이고 있는지 판단
	Owner->bUseControllerRotationYaw =
		UKismetMathLibrary::NotEqual_VectorVector
		(
			Owner->GetCharacterMovement()->GetCurrentAcceleration(), // 가속도
			FVector(0, 0, 0)
		);
}

void UAct_Aiming::EndAction()
{
	Super::EndAction();

	Owner->GetWeaponComponent()->SetAiming(false);
	Owner->bUseControllerRotationYaw = false;
}
