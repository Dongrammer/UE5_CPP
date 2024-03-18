#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

enum class EActionType : uint8;
class UBaseAction;

UCLASS()
class UE5_CPP_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Body;

	TMap<EActionType, UBaseAction*> ActionsPtr;

public:	
	ABaseWeapon();

	void CreateAction(EActionType Type, TSubclassOf<UBaseAction> ActionClass);

	FORCEINLINE UBaseAction* GetAction(EActionType Type) { return ActionsPtr.FindRef(Type); }

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
};
