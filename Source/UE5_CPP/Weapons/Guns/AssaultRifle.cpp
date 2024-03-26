#include "Weapons/Guns/AssaultRifle.h"
#include "Helper.h"

#include "Weapons/WeaponDataAsset.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Engine/StaticMeshActor.h"
#include "NiagaraFunctionLibrary.h"
#include "Weapons/WeaponEnum.h"

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

	CurrentRound = MaxRound = Data->MaxAmmoInMagazine;
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

	// �Ѿ��� ���� �־ �ݹ��� �� ����
	FireCounter++;
	CurrentRound--;

	// 1. ���� ���
	FVector Location = MuzzleFlash->GetComponentLocation();	// �Ҹ��� ����� ������Ʈ
	UGameplayStatics::PlaySoundAtLocation(this, FireSound, Location, FRotator());

	// 2. ����Ʈ
	Location = MuzzleFlash->GetComponentLocation();
	FRotator Rotation = MuzzleFlash->GetComponentRotation();
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FireEffect, Location, Rotation);

	// 3. �Ѿ� �߻�

}

void AAssaultRifle::EjectShell()
{
	Super::EjectShell();

	FVector Location = Body->GetSocketLocation("ShellEject");	// ź�ǰ� ������ ���� �̸�
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
