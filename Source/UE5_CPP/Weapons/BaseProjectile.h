#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.generated.h"

/*
	��� �Ѿ˰� �̻��Ͽ� ���� �θ� Ŭ�����Դϴ�.
	���Ŀ� Static Mesh�� ����ϴ� Ŭ������ Skeletal Mesh�� ����ϴ� Ŭ������ �и��� �����Դϴ�.
	����Ͻ� ���� Static Mesh projectile Ȥ�� Skeletal Mesh Projectile�� ����ϼ���.
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
