#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UWeaponComponent;

UCLASS()
class UE5_CPP_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UWeaponComponent* WeaponComponent;

public:
	ABaseCharacter();

protected:
	virtual void BeginPlay() override;

	void SetCharacterMovement();
};
