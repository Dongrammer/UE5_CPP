#include "Weapons/Guns/AssaultRifle.h"
#include "Helper.h"

#include "Weapons/WeaponDataAsset.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Engine/StaticMeshActor.h"
#include "NiagaraFunctionLibrary.h"
#include "Weapons/WeaponEnum.h"
#include "Characters/BaseCharacter.h"
#include "Weapons/BaseProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

AAssaultRifle::AAssaultRifle()
{
	Magazine = Helper::CreateSceneComponent<UStaticMeshComponent>(this, "Magazine", Body, "magazine");
	MuzzleFlash = Helper::CreateSceneComponent<UStaticMeshComponent>(this, "MuzzleFlash", Body, "silencer");
	Accessory = Helper::CreateSceneComponent<UStaticMeshComponent>(this, "Accessory", Body, "pointer");
	Scope = Helper::CreateSceneComponent<UStaticMeshComponent>(this, "Scope", Body, "scope");
	UnderBarrel = Helper::CreateSceneComponent<USkeletalMeshComponent>(this, "UnderBarrel", Body, "accessory");

	Magazine->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MuzzleFlash->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Accessory->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Scope->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	UnderBarrel->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAssaultRifle::SetData(UWeaponDataAsset* Data)
{
	Super::SetData(Data);

	RPM = 60.0f / Data->RoundsPerMinute;

	Shell = Data->Shell;
	Round = Data->Round;
	FireSound = Data->FireSound;
	FireEffect = Data->FireEffect;

	BulletClass = Data->BulletClass;
	InitSpeed = Data->InitSpeed;
	GravityScale = Data->GravityScale;
	bRotationFollowsVelocity = Data->bRotationFollowsVelocity;
}

void AAssaultRifle::Fire()
{
	Super::Fire();

	if (CurrentRound <= 0)
		WeaponState = EWeaponState::FireEmpty;
	else if (CurrentRound <= MaxRound)
		WeaponState = EWeaponState::Fire;
}

void AAssaultRifle::HoldFire()
{
	Super::HoldFire();

	FireCounter = 0;

	if (CurrentRound <= 0)
		WeaponState = EWeaponState::FireEmpty;
	else
		WeaponState = EWeaponState::Idle;
}

void AAssaultRifle::Reload()
{
	Super::Reload();
}

void AAssaultRifle::BulletFire()
{
	Super::BulletFire();

	if (CurrentRound <= 0)
	{
		WeaponState = EWeaponState::FireEmpty;
		return;
	}

	// 총알이 남아 있어서 격발이 된 상태
	FireCounter++;
	CurrentRound--;

	// 1. 사운드 재생
	FVector Location = MuzzleFlash->GetComponentLocation();	// 소리가 재생될 컴포넌트
	UGameplayStatics::PlaySoundAtLocation(this, FireSound, Location, FRotator());

	// 2. 이펙트
	Location = MuzzleFlash->GetComponentLocation();
	FRotator Rotation = MuzzleFlash->GetComponentRotation();
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FireEffect, Location, Rotation);

	// 3. 총알 발사
	FActorSpawnParameters Parameter;
	Parameter.Owner = GetOwner();	// 발사한 캐릭터

	ABaseProjectile* Bullet = GetWorld()->SpawnActor<ABaseProjectile>
		(
			BulletClass,
			Location,
			Rotation,
			Parameter
		);

	const FVector FwdVector = Body->GetForwardVector();
	Bullet->GetProjectileComponent()->Velocity = (FwdVector * InitSpeed);
	Bullet->GetProjectileComponent()->ProjectileGravityScale = GravityScale;
	Bullet->GetProjectileComponent()->bRotationFollowsVelocity = bRotationFollowsVelocity;
	Bullet->SetLifeSpan(10);
}

void AAssaultRifle::EjectShell()
{
	Super::EjectShell();

	FVector Location = Body->GetSocketLocation("ShellEject");	// 탄피가 생성될 소켓 이름
	FRotator Rotation = FRotator();
	Rotation.Yaw = FMath::FRandRange(60.0f, 130.0f);

	AStaticMeshActor* TShell = GetWorld()->SpawnActor<AStaticMeshActor>
		(
			AStaticMeshActor::StaticClass(),
			Location,
			Rotation
		);

	TShell->SetMobility(EComponentMobility::Movable);
	TShell->GetStaticMeshComponent()->SetStaticMesh(Shell);
	TShell->SetLifeSpan(10.0f);
	TShell->GetStaticMeshComponent()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	TShell->GetStaticMeshComponent()->SetSimulatePhysics(true);

	FVector Force = Body->GetRightVector();
	Force *= FMath::FRandRange(300.0f, 500.0f);
	TShell->GetStaticMeshComponent()->AddForce(Force);
}

void AAssaultRifle::DryFire()
{
	Super::DryFire();

	FireCounter = 0;

	const FVector Location = Body->GetSocketLocation("ShellEject");
	UGameplayStatics::PlaySoundAtLocation(this, DrySound, Location, FRotator());
}

void AAssaultRifle::CheckFire()
{
	Super::CheckFire();
}

void AAssaultRifle::DropMagazine()
{
	Super::DropMagazine();

	// 1. 장착되어 있는 탄창 투명화
	Magazine->SetVisibility(false);

	// 2. 같은 위치에 떨어질 탄창 스폰
	AStaticMeshActor* DropMagazine = GetWorld()->SpawnActor<AStaticMeshActor>
		(
			AStaticMeshActor::StaticClass(),
			Magazine->GetComponentLocation(),
			Magazine->GetComponentRotation()
		);

	// 3. 탄창 물리 설정
	DropMagazine->SetMobility(EComponentMobility::Movable);
	DropMagazine->GetStaticMeshComponent()->SetStaticMesh(Magazine->GetStaticMesh());
	DropMagazine->GetStaticMeshComponent()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	DropMagazine->GetStaticMeshComponent()->SetSimulatePhysics(true);

	// 4. 수명 설정
	DropMagazine->SetLifeSpan(60);
}

void AAssaultRifle::SpawnNewMagazine()
{
	Super::SpawnNewMagazine();

	// 1. 탄창 비투명화
	Magazine->SetVisibility(true);

	// 2. 탄창 캐릭터 손에 부착
	Magazine->AttachToComponent
	(
		Cast<ABaseCharacter>(GetOwner())->GetMesh(),
		FAttachmentTransformRules::KeepRelativeTransform,
		"Rifle_Magazine"
	);
}

void AAssaultRifle::LoadedNewMagazine()
{
	// 1. 총기에 탄창 붙이기
	Magazine->AttachToComponent
	(
		this->Body,
		FAttachmentTransformRules::KeepRelativeTransform,
		"magazine"
	);

	// 2. 탄창 충전
	CurrentRound = MaxRound;
}
