#include "Weapons/Guns/AssaultRifle.h"
#include "Helper.h"

#include "Weapons/WeaponDataAsset.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Engine/StaticMeshActor.h"
#include "NiagaraFunctionLibrary.h"

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

	// Ÿ�̸� ����
	GetWorldTimerManager().SetTimer(FireProceduresHandle, this, &AAssaultRifle::FireProcedures, RPM, true);

	// ���� �� ����
	GetWorldTimerManager().PauseTimer(FireProceduresHandle);
}

void AAssaultRifle::Fire()
{
	Super::Fire();

	GetWorldTimerManager().UnPauseTimer(FireProceduresHandle);
}

void AAssaultRifle::HoldFire()
{
	Super::HoldFire();

	GetWorldTimerManager().PauseTimer(FireProceduresHandle);
}

void AAssaultRifle::FireProcedures()
{
	// 1. ���� ���
	FVector Location = MuzzleFlash->GetComponentLocation();	// �Ҹ��� ����� ������Ʈ
	UGameplayStatics::PlaySoundAtLocation(this, FireSound, Location, FRotator());

	// 2. ź�� ����
	Location = Body->GetSocketLocation("ShellEject");	// ź�ǰ� ������ ���� �̸�
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

	// 3. ����Ʈ
	Location = MuzzleFlash->GetComponentLocation();
	Rotation = MuzzleFlash->GetComponentRotation();
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FireEffect, Location, Rotation);

	// 4. �Ѿ�

}
