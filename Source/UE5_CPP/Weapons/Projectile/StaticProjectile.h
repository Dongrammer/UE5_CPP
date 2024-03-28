#pragma once

#include "CoreMinimal.h"
#include "Weapons/BaseProjectile.h"
#include "StaticProjectile.generated.h"

/**
 *	애니메이션이 없는 총알 등을 만들 때 사용합니다.
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
