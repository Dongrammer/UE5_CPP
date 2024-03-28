#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponDataAsset.generated.h"

enum class EWeaponType : uint8;
enum class EActionType : uint8;
class ABaseWeapon;
class UBaseAction;
class UNiagaraSystem;
class USoundCue;
class ABaseProjectile;

UCLASS()
class UE5_CPP_API UWeaponDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Required")
	TSubclassOf<ABaseWeapon> WeaponClass;	// ���� Ŭ����

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Required")
	FName HandleSocketName;		// ������ ����

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Required")
	FName HolderSocketName;		// ���� ����

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Required")
	EWeaponType WeaponType;		// ���� ����
	
	/* =============================================================== */

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Property")
	float RoundsPerMinute = 1.0f;		// �����

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Property")
	float Damage = 1.0f;		// ���ݷ�

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Property")
	FVector2D Rebound;			// �ݵ�

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Property")
	int MaxAmmoCapacity;		// �ִ� �Ѿ� ���� ��

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Property")
	float Weight;				// ����

	/* =============================================================== */

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Magazine")
	int MaxAmmoInMagazine;	// �ִ� �Ѿ� ���� ��

	UPROPERTY(EditDefaultsOnly, Category = "Magazine")
	UStaticMesh* Round;		// ź��

	UPROPERTY(EditDefaultsOnly, Category = "Magazine")
	UStaticMesh* Shell;		// ź��
	
	UPROPERTY(EditDefaultsOnly, Category = "Magazine")
	USoundCue* FireSound;	// �߻� �Ҹ�

	UPROPERTY(EditDefaultsOnly, Category = "Magazine")
	UNiagaraSystem* FireEffect;	// �߻� ����Ʈ

	/* =============================================================== */

	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
	TSubclassOf<ABaseProjectile> BulletClass;

	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
	float InitSpeed = 10.0;

	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
	bool bRotationFollowsVelocity = true;

	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
	float GravityScale = 1.0f;

	/* =============================================================== */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Actions")
	TMap<EActionType, TSubclassOf<UBaseAction>> Actions;
};