#include "Weapons/BaseProjectile.h"

#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Helper.h"
#include "Engine/DecalActor.h"
#include "NiagaraActor.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "Engine/StaticMeshActor.h"

DEFINE_LOG_CATEGORY(BulletLog);

ABaseProjectile::ABaseProjectile()
{
 	PrimaryActorTick.bCanEverTick = true;

	Scene = Helper::CreateSceneComponent<USceneComponent>(this, "Scene");
	Collision = Helper::CreateSceneComponent<UBoxComponent>(this, "Collision", Scene);
	ProjectileMovementComponent = Helper::CreateActorComponent<UProjectileMovementComponent>(this, "Projectile Movement Comp");
}

void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collision->SetCollisionProfileName("OverlapAllDynamic");

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ABaseProjectile::OnOverlap);
}

void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 1. 오버랩된 객체가 벽이나 바닥 등의 객체인지 판단
	AStaticMeshActor* BackGround = Cast<AStaticMeshActor>(OtherActor);

	if (BackGround)
	{
		// 총알이 날아가는 방향 반대로 100만큼 이동
		FVector Velocity = GetVelocity();
		Velocity = Velocity.GetSafeNormal();

		// 충돌 지점에서 날아가는 방향의 반대로 100만큼 이동시킨 지점
		FVector Start = GetActorLocation() + (-Velocity * 100.0f);

		// 위 지점에서 300만큼 날아가는 방향의 지점
		FVector End = Start + (Velocity * 300.0f);

		// 충돌할 액터 타입
		FCollisionObjectQueryParams Type;
		Type.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic);
		
		// 무시할 액터 추가
		FCollisionQueryParams CollisionParams;

		TArray<AActor*> IgnoreActors;
		GetOwner()->GetAllChildActors(IgnoreActors); // 소유자가 가지고 있는 모든 자식 액터(총, 총알 등)
		IgnoreActors.Add(GetOwner()); // 소유자 추가
		CollisionParams.AddIgnoredActors(IgnoreActors);
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 10);

		// 라인트레이스
		FHitResult HittedActor;
		bool bHit = GetWorld()->LineTraceSingleByObjectType(HittedActor, Start, End, Type, CollisionParams);
		

		if (bHit)
		{
			// UE_LOG(BulletLog, Log, L"%s", *OtherActor->GetName());
			// 라인트레이스 이후에 맞은 장소에 데칼 스폰
			FRotator rotator = FRotationMatrix::MakeFromX(HittedActor.ImpactNormal).Rotator();
			ADecalActor* DecalActor = GetWorld()->SpawnActor<ADecalActor>
				(
					ADecalActor::StaticClass(),
					HittedActor.ImpactPoint,
					FRotator()
				);
			DecalActor->SetLifeSpan(10.0);
			DecalActor->SetActorScale3D(FVector(0.5, 0.05, 0.05));
			DecalActor->SetDecalMaterial(Helper::GetAssetDynamic<UMaterialInterface>(L"/Game/WeaponKit/FX/MI_BulletHole_Decal_WK"));
			DecalActor->SetActorRotation(rotator);

			// 이펙트 생성
			ANiagaraActor* Effect = GetWorld()->SpawnActor<ANiagaraActor>
				(
					ANiagaraActor::StaticClass(),
					SweepResult.ImpactPoint,
					FRotator()
				);
			Effect->GetNiagaraComponent()->SetAsset(Helper::GetAssetDynamic<UNiagaraSystem>(L"/Game/WeaponKit/FX/NS_BulletImpactPuff_WK"));
			Effect->SetLifeSpan(2.0);
			Effect->SetActorScale3D(FVector(3));
			Effect->SetActorRotation(rotator);

			// HittedActor.GetActor() 를 통해 데미지 등 작업 수행 가능
		}
	}

	// 총알 삭제
	this->Destroy();
}

