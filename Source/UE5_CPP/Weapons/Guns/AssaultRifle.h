#pragma once

#include "CoreMinimal.h"
#include "Weapons/BaseWeapon.h"
#include "AssaultRifle.generated.h"

class USoundCue;
class UNiagaraSystem;
class ABaseProjectile;

UCLASS()
class UE5_CPP_API AAssaultRifle : public ABaseWeapon
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Magazine;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* MuzzleFlash;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Accessory;		// 장식품

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Scope;			// 조준경

	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* UnderBarrel;	// 탄창

	UPROPERTY()
	UStaticMesh* Round;

	UPROPERTY()
	UStaticMesh* Shell;

	UPROPERTY()
	USoundCue* FireSound;

	UPROPERTY()
	UNiagaraSystem* FireEffect;

	float RPM;

	UPROPERTY()
	TSubclassOf<ABaseProjectile> BulletClass;

	float InitSpeed = 2000;
	float GravityScale;
	bool bRotationFollowsVelocity;

public:
	AAssaultRifle();

	virtual void SetData(UWeaponDataAsset* Data) override;

	virtual void Fire() override;
	virtual void HoldFire() override;
	virtual void Reload() override;

	virtual void BulletFire() override;
	virtual void EjectShell() override;
	virtual void DryFire() override;
	virtual void CheckFire() override;

	virtual void DropMagazine() override;
	virtual void SpawnNewMagazine() override;
	virtual void LoadedNewMagazine() override;
};
