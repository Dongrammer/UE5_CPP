#include "Weapons/BaseWeapon.h"
#include "Helper.h"

#include "Actions/ActionEnum.h"
#include "Actions/BaseAction.h"
#include "Characters/BaseCharacter.h"
#include "Sound/SoundCue.h"
#include "WeaponDataAsset.h"

ABaseWeapon::ABaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	Body = Helper::CreateSceneComponent<USkeletalMeshComponent>(this, "Body");
	
	DrySound = Helper::GetAsset<USoundCue>(L"/Game/WeaponKit/FX/Cue/A_Gun_FireDry_WK_Cue");
}

void ABaseWeapon::CreateAction(EActionType Type, TSubclassOf<UBaseAction> ActionClass)
{
	if (ActionClass == nullptr) return;

	UBaseAction* Action = NewObject<UBaseAction>(this, ActionClass);
	ActionsPtr.Add(Type, Action);
	Action->SetOwner(Cast<ABaseCharacter>(GetOwner()));
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseWeapon::SetData(UWeaponDataAsset* Data)
{
	CurrentRound = MaxRound = Data->MaxAmmoInMagazine;
}

void ABaseWeapon::Fire()
{
	bPressed = true;
}

void ABaseWeapon::HoldFire()
{
	bPressed = false;
}

void ABaseWeapon::Reload()
{
}

void ABaseWeapon::BulletFire()
{
}

void ABaseWeapon::EjectShell()
{
}

void ABaseWeapon::DryFire()
{
}

void ABaseWeapon::CheckFire()
{
}

void ABaseWeapon::DropMagazine()
{
}

void ABaseWeapon::SpawnNewMagazine()
{
}

void ABaseWeapon::LoadedNewMagazine()
{
}

