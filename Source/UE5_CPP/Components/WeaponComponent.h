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

private:
	/* ABP Read Value */
	bool Swapping = false;
	EWeaponType CurrentWeaponType;

protected:
	UPROPERTY(EditAnywhere, Category = "WeaponClass")
	TMap<EWeaponSlot, UWeaponDataAsset*> WeaponAssets;

private:
	TMap<EWeaponSlot, ABaseWeapon*> Weapons;
	ABaseCharacter* Owner;
	ABaseWeapon* CurrentWeapon;
	EWeaponSlot SelectedWeaponSlot;

public:	
	UWeaponComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FORCEINLINE EWeaponSlot GetSelectedWeaponSlot() { return SelectedWeaponSlot; }
	FORCEINLINE EWeaponType GetCurrentWeaponType() { return CurrentWeaponType; }
	FORCEINLINE bool IsSwapping() { return Swapping; }
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

public:
	void EquipWeapon(EWeaponSlot Slot);
	void AttachWeapon(EWeaponSlot Slot, EAttachType AttachType);
};
