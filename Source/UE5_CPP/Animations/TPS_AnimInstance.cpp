#include "Animations/TPS_AnimInstance.h"

#include "Kismet/KismetMathLibrary.h"
#include "KismetAnimationLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Characters/BaseCharacter.h"
#include "Components/WeaponComponent.h"
#include "Weapons/WeaponEnum.h"

void UTPS_AnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<ABaseCharacter>(TryGetPawnOwner());
	if (Owner != nullptr)
	{
		Movement = Owner->GetCharacterMovement();
		WeaponComponent = Owner->GetWeaponComponent();
	}
}

void UTPS_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!Owner) return;
	UpdateBlendSpaceVariable();
	UpdateAimOffsetVariable();
	UpdateWeaponComponentVariable();
}

void UTPS_AnimInstance::UpdateBlendSpaceVariable()
{

	if (!Movement || !Owner) return;
	bIsFalling = Movement->IsFalling();

	Velocity = Owner->GetVelocity();
	Speed = Velocity.Size2D();

	Rotation = FRotator(0, Owner->GetControlRotation().Yaw, 0);
	Direction = UKismetAnimationLibrary::CalculateDirection(Velocity, Rotation);

	// 두 조건이 모두 맞으면 움직이는 상태
	bShouldMove = UKismetMathLibrary::NotEqual_VectorVector(Movement->GetCurrentAcceleration(), FVector(0, 0, 0), 0.0f) && Speed > 3.0f;
}

void UTPS_AnimInstance::UpdateAimOffsetVariable()
{
	// 컨트롤러와 캐릭터 메시의 각도 차이를 구함
	const FRotator DeltaRotator = UKismetMathLibrary::NormalizedDeltaRotator(Owner->GetControlRotation(), Owner->GetActorRotation());
	Yaw = DeltaRotator.Yaw;
	Pitch = DeltaRotator.Pitch;
}

void UTPS_AnimInstance::UpdateWeaponComponentVariable()
{
	if (!WeaponComponent) return;
	bSwapping = WeaponComponent->bSwapping;
	bAiming = WeaponComponent->bAiming;
	WeaponType = WeaponComponent->GetCurrentWeaponType();
	bReload = WeaponComponent->bReload;
}
