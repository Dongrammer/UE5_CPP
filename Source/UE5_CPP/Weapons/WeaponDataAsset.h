#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponDataAsset.generated.h"

enum class EWeaponType : uint8;
class ABaseWeapon;

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
	int MaxAmmoInMagazine;	// �ִ� �Ѿ� ���� ��

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Property")
	int MaxAmmoCapacity;		// �ִ� �Ѿ� ���� ��

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Property")
	float Weight;				// ����
};