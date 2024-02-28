#include "Animations/TPS_AnimInstance.h"

#include "Kismet/KismetMathLibrary.h"
#include "KismetAnimationLibrary.h"
#include "Characters/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UTPS_AnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<ABaseCharacter>(TryGetPawnOwner());
	if (Owner != nullptr)
		Movement = Owner->GetCharacterMovement();

}

void UTPS_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!Movement || !Owner) return;

	bIsFalling = Movement->IsFalling();

	Velocity = Owner->GetVelocity();
	Speed = Velocity.Size2D();
	
	Rotation = FRotator(0, Owner->GetControlRotation().Yaw, 0);
	Direction = UKismetAnimationLibrary::CalculateDirection(Velocity, Rotation);

	// 두 조건이 모두 맞으면 움직이는 상태
	bShouldMove = UKismetMathLibrary::NotEqual_VectorVector(Movement->GetCurrentAcceleration(), FVector(0, 0, 0), 0.0f) && Speed > 3.0f;
}
