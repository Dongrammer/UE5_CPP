#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TPS_AnimInstance.generated.h"

// 전방선언
class ABaseCharacter;
class UCharacterMovementComponent;
class UWeaponComponent;
enum class EWeaponType : uint8;

UCLASS()
class UE5_CPP_API UTPS_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	void UpdateBlendSpaceVariable();
	void UpdateAimOffsetVariable();
	void UpdateWeaponComponentVariable();

private:
	UPROPERTY(BlueprintReadOnly, Category = "BlendSpace", meta = (AllowPrivateAccess = "true"))
	float Direction;

	UPROPERTY(BlueprintReadOnly, Category = "BlendSpace", meta = (AllowPrivateAccess = "true"))
	float Speed;

	UPROPERTY(BlueprintReadOnly, Category = "BlendSpace", meta = (AllowPrivateAccess = "true"))
	FVector Velocity;

	UPROPERTY(BlueprintReadOnly, Category = "BlendSpace", meta = (AllowPrivateAccess = "true"))
	bool bIsFalling;

	// 지금 움직이고 있는지 판단하는 변수
	UPROPERTY(BlueprintReadOnly, Category = "BlendSpace", meta = (AllowPrivateAccess = "true"))
	bool bShouldMove;

	// Aimoffset
	UPROPERTY(BlueprintReadOnly, Category = "Aimoffset", meta = (AllowPrivateAccess = "true"))
	float Yaw;

	UPROPERTY(BlueprintReadOnly, Category = "Aimoffset", meta = (AllowPrivateAccess = "true"))
	float Pitch;

	// WeaponComponent에서 받아오는 변수
	UPROPERTY(BlueprintReadOnly, Category = "WeaponComponent", meta = (AllowPrivateAccess = "true"))
	EWeaponType WeaponType;

	UPROPERTY(BlueprintReadOnly, Category = "WeaponComponent", meta = (AllowPrivateAccess = "true"))
	bool Swapping;

private:
	ABaseCharacter* Owner;

	UCharacterMovementComponent* Movement;
	UWeaponComponent* WeaponComponent;
	FRotator Rotation;
};
