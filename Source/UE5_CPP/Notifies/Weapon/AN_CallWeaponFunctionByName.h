#pragma once

#include "CoreMinimal.h"
#include "Notifies/Weapon/AN_WeaponMesh.h"
#include "AN_CallWeaponFunctionByName.generated.h"

/**
 * 함수 이름으로 BaseWeapon에 있는 함수를 호출해주는 역할을 하는 노티파이입니다.
 */
UCLASS()
class UE5_CPP_API UAN_CallWeaponFunctionByName : public UAN_WeaponMesh
{
	GENERATED_BODY()
	
private:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

public:
	virtual FString GetNotifyName_Implementation() const override;

private:
	UPROPERTY(EditInstanceOnly, meta = (AllowPrivateAccess = "true"))
	FName FunctionName;
};
