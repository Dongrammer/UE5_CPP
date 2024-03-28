#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.generated.h"

/*
	모든 총알과 미사일에 대한 부모 클래스입니다.
	이후에 Static Mesh를 사용하는 클래스와 Skeletal Mesh를 사용하는 클래스로 분리될 예정입니다.
	사용하실 때는 Static Mesh projectile 혹은 Skeletal Mesh Projectile을 사용하세요.
*/

DECLARE_LOG_CATEGORY_EXTERN(BulletLog, Log, All);

class UBoxComponent;
class UProjectileMovementComponent;

UCLASS(Abstract)
class UE5_CPP_API ABaseProjectile : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* Scene;

	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
	UBoxComponent* Collision;

	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
	UProjectileMovementComponent* ProjectileMovementComponent;

public:	
	ABaseProjectile();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE UProjectileMovementComponent* GetProjectileComponent() { return ProjectileMovementComponent; }

private:
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
