#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

enum class EActionType : uint8;
class UBaseAction;
class UWeaponDataAsset;

UCLASS()
class UE5_CPP_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Body;

	UPROPERTY()
	TMap<EActionType, UBaseAction*> ActionsPtr;

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
};
