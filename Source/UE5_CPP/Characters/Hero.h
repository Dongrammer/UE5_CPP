#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Logging/LogMacros.h"
#include "Hero.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UInputDataAsset;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(HeroLog, Log, All);

// Weapon Select Delegate
DECLARE_MULTICAST_DELEGATE(FMainWeaponSelect);
DECLARE_MULTICAST_DELEGATE(FSecondaryWeaponSelect);
DECLARE_MULTICAST_DELEGATE(FThrowableWeaponSelect);
DECLARE_MULTICAST_DELEGATE_OneParam(FScrollSelect, uint8);

// Action Delegate
DECLARE_MULTICAST_DELEGATE(FDoMainAction);
DECLARE_MULTICAST_DELEGATE(FEndMainAction);
DECLARE_MULTICAST_DELEGATE(FDoSubAction);
DECLARE_MULTICAST_DELEGATE(FEndSubAction);
DECLARE_MULTICAST_DELEGATE(FDoAvoidAction);
DECLARE_MULTICAST_DELEGATE(FEndAvoidAction);

DECLARE_MULTICAST_DELEGATE(FDoReloadAction);


UCLASS()
class UE5_CPP_API AHero : public ABaseCharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* KeyMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputDataAsset* InputAsset;

public:
	FMainWeaponSelect DMainWeaponSelect;
	FSecondaryWeaponSelect DSecondaryWeaponSelect;
	FThrowableWeaponSelect DThrowableWeaponSelect;
	FScrollSelect DScrollSelect;

	FDoMainAction DDoMainAction;
	FEndMainAction DEndMainAction;
	FDoSubAction DDoSubAction;
	FEndSubAction DEndSubAction;
	FDoAvoidAction DDoAvoidAction;
	FEndAvoidAction DEndAvoidAction;

	FDoReloadAction DDoReloadAction;

public:
	AHero();

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	void SelectMainWeapon();
	void SelectSecondaryWeapon();
	void SelectThrowableWeapon();
	void ChooseWeaponByScroll(const FInputActionValue& Value);

	void DoMainAction();
	void EndMainAction();
	void DoSubAction();
	void EndSubAction();

	void DoAvoid();
	void EndAvoid();

	void DoReloadAction();

public:
	virtual void Tick(float DeltaSecond) override;

	FORCEINLINE USpringArmComponent* GetCameraArm() const { return CameraArm; }
	FORCEINLINE UCameraComponent* GetCamera() const { return Camera; }

private:
	void CreateCamera();

	void MappingInputAsset(UEnhancedInputComponent* Comp);
};
