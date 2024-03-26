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

UCLASS()
class UE5_CPP_API UWeaponDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Required")
	TSubclassOf<ABaseWeapon> WeaponClass;	// 무기 클래스

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Required")
	FName HandleSocketName;		// 손잡이 소켓

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Required")
	FName HolderSocketName;		// 장착 소켓

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Required")
	EWeaponType WeaponType;		// 장착 소켓
	
	/* =============================================================== */

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Property")
	float RoundsPerMinute = 1.0f;		// 연사력

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Property")
	float Damage = 1.0f;		// 공격력

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Property")
	FVector2D Rebound;			// 반동

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Property")
	int MaxAmmoCapacity;		// 최대 총알 보유 수

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Property")
	float Weight;				// 무게

	/* =============================================================== */

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Magazine")
	int MaxAmmoInMagazine;	// 최대 총알 장전 수

	UPROPERTY(EditDefaultsOnly, Category = "Magazine")
	UStaticMesh* Round;		// 탄약

	UPROPERTY(EditDefaultsOnly, Category = "Magazine")
	UStaticMesh* Shell;		// 탄피
	
	UPROPERTY(EditDefaultsOnly, Category = "Magazine")
	USoundCue* FireSound;	// 발사 소리

	UPROPERTY(EditDefaultsOnly, Category = "Magazine")
	UNiagaraSystem* FireEffect;	// 발사 이펙트

	/* =============================================================== */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Actions")
	TMap<EActionType, TSubclassOf<UBaseAction>> Actions;
};