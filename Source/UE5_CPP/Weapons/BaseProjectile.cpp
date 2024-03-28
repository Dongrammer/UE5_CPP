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
	// 1. �������� ��ü�� ���̳� �ٴ� ���� ��ü���� �Ǵ�
	AStaticMeshActor* BackGround = Cast<AStaticMeshActor>(OtherActor);

	if (BackGround)
	{
		// �Ѿ��� ���ư��� ���� �ݴ�� 100��ŭ �̵�
		FVector Velocity = GetVelocity();
		Velocity = Velocity.GetSafeNormal();

		// �浹 �������� ���ư��� ������ �ݴ�� 100��ŭ �̵���Ų ����
		FVector Start = GetActorLocation() + (-Velocity * 100.0f);

		// �� �������� 300��ŭ ���ư��� ������ ����
		FVector End = Start + (Velocity * 300.0f);

		// �浹�� ���� Ÿ��
		FCollisionObjectQueryParams Type;
		Type.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic);
		
		// ������ ���� �߰�
		FCollisionQueryParams CollisionParams;

		TArray<AActor*> IgnoreActors;
		GetOwner()->GetAllChildActors(IgnoreActors); // �����ڰ� ������ �ִ� ��� �ڽ� ����(��, �Ѿ� ��)
		IgnoreActors.Add(GetOwner()); // ������ �߰�
		CollisionParams.AddIgnoredActors(IgnoreActors);
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 10);

		// ����Ʈ���̽�
		FHitResult HittedActor;
		bool bHit = GetWorld()->LineTraceSingleByObjectType(HittedActor, Start, End, Type, CollisionParams);
		

		if (bHit)
		{
			// UE_LOG(BulletLog, Log, L"%s", *OtherActor->GetName());
			// ����Ʈ���̽� ���Ŀ� ���� ��ҿ� ��Į ����
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

			// ����Ʈ ����
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

			// HittedActor.GetActor() �� ���� ������ �� �۾� ���� ����
		}
	}

	// �Ѿ� ����
	this->Destroy();
}

