#pragma once

#include "CoreMinimal.h"
#include "Weapons/BaseProjectile.h"
#include "StaticProjectile.generated.h"

/**
 *	�ִϸ��̼��� ���� �Ѿ� ���� ���� �� ����մϴ�.
 */
UCLASS()
class UE5_CPP_API AStaticProjectile : public ABaseProjectile
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Bullet;

public:
	AStaticProjectile();
};
