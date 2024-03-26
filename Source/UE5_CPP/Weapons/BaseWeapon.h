#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseWeapon.generated.h"

enum class EActionType : uint8;
enum class EWeaponState : uint8;
class UBaseAction;
class UWeaponDataAsset;
class SoundCue;

UCLASS()
class UE5_CPP_API ABaseWeapon : public APawn
{
	GENERATED_BODY()
	
public:
	EWeaponState WeaponState;

protected:
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Body;

	UPROPERTY()
	TMap<EActionType, UBaseAction*> ActionsPtr;

	UPROPERTY()
	USoundCue* DrySound;

	int CurrentRound;	// źâ�� �ִ� �Ѿ� ��
	int MaxRound;		// �ִ� �Ѿ� ��
	int FireCounter;	// �ѹ��� �߻��� �Ѿ� ��

	bool bPressed = false;

public:	
	ABaseWeapon();

	void CreateAction(EActionType Type, TSubclassOf<UBaseAction> ActionClass);

	FORCEINLINE UBaseAction* GetAction(EActionType Type) { return ActionsPtr.FindRef(Type); }

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetData(UWeaponDataAsset* Data);

	virtual void Fire();
	virtual void HoldFire();
	virtual void Reload();

	// Notify
	UFUNCTION()
	virtual void BulletFire();
	UFUNCTION()
	virtual void EjectShell();
	UFUNCTION()
	virtual void DryFire();
	UFUNCTION()
	virtual void CheckFire();
};
