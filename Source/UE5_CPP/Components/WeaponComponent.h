#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class ABaseWeapon;
class UWeaponDataAsset;
class ABaseCharacter;
enum class EWeaponSlot : uint8;
enum class EWeaponType : uint8;
enum class EAttachType : uint8;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_CPP_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	/* ABP Read Value */
	bool bSwapping = false;
	bool bAiming = false;
	EWeaponType CurrentWeaponType;

protected:
	UPROPERTY(EditAnywhere, Category = "WeaponClass")
	TMap<EWeaponSlot, UWeaponDataAsset*> WeaponAssets;

private:
	TMap<EWeaponSlot, ABaseWeapon*> Weapons;
	ABaseCharacter* Owner;

	UPROPERTY()
	ABaseWeapon* CurrentWeapon;

	EWeaponSlot CurrentWeaponSlot;

public:	
	UWeaponComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FORCEINLINE EWeaponSlot GetCurrentWeaponSlot() { return CurrentWeaponSlot; }
	FORCEINLINE EWeaponType GetCurrentWeaponType() { return CurrentWeaponType; }
	FORCEINLINE bool IsSwapping() { return bSwapping; }
	FORCEINLINE bool IsAiming() { return bAiming; }
	FORCEINLINE UWeaponDataAsset* GetAsset(const EWeaponSlot Key) { return WeaponAssets.FindRef(Key); }
	FORCEINLINE ABaseWeapon* GetWeapon(const EWeaponSlot Key) { return Weapons.FindRef(Key); }
		
private:
	void SpawnWeapons();

	UFUNCTION()
	void DoMainAction();

	UFUNCTION()
	void EndMainAction();

	UFUNCTION()
	void DoSubAction();

	UFUNCTION()
	void EndSubAction();

	UFUNCTION()
	void DoAvoidAction();

	UFUNCTION()
	void EndAvoidAction();

	UFUNCTION()
	void DoReloadAction();

	/* ========== Select Weapon ========== */
	UFUNCTION()
	void SelectMainWeapon();

	UFUNCTION()
	void SelectSecondaryWeapon();

	UFUNCTION()
	void SelectThrowableWeapon();

	UFUNCTION()
	void ChooseWeaponByScroll(uint8 InValue);

public:
	void EquipWeapon(EWeaponSlot Slot);
	void AttachWeapon(EWeaponSlot Slot, EAttachType AttachType);

	FORCEINLINE void SetAiming(bool AimState) { bAiming = AimState; }
};

#define CALL_ACTION(ActionType, ActionTiming) \
	if(UBaseAction* Action = CurrentWeapon->GetAction(ActionType)) \
		Action->ExecuteAction(ActionTiming)