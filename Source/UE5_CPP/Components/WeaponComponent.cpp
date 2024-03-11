#include "Components/WeaponComponent.h"
#include "Weapons/WeaponEnum.h"
#include "Weapons/BaseWeapon.h"
#include "Characters/BaseCharacter.h"
#include "Weapons/WeaponDataAsset.h"
#include "Characters/Hero.h"

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ABaseCharacter>(GetOwner());

	SpawnWeapons();
	SelectedWeaponSlot = EWeaponSlot::E_Main;
	CurrentWeaponType = GetAsset(SelectedWeaponSlot)->WeaponType;

	if (AHero* Hero = Cast<AHero>(Owner))
	{
		Hero->DDoMainAction.AddUFunction(this, "DoMainAction");
		Hero->DEndMainAction.AddUFunction(this, "EndMainAction");

		Hero->DDoSubAction.AddUFunction(this, "DoSubAction");
		Hero->DEndSubAction.AddUFunction(this, "EndSubAction");

		Hero->DDoAvoidAction.AddUFunction(this, "DoAvoidAction");
		Hero->DEndAvoidAction.AddUFunction(this, "EndAvoidAction");

		Hero->DDoReloadAction.AddUFunction(this, "DoReloadAction");
	}
}

void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UWeaponComponent::SpawnWeapons()
{
	for (auto& Weapon : WeaponAssets)
	{
		if (!Weapon.Value) return;

		FActorSpawnParameters SpawnParameter;
		SpawnParameter.Owner = GetOwner();

		ABaseWeapon* Temp = Cast<ABaseWeapon>(GetOwner()->GetWorld()->SpawnActor<AActor>(Weapon.Value->WeaponClass, FVector(), FRotator(), SpawnParameter));

		if (Temp)
		{
			Weapons.Add(Weapon.Key, Temp);
			AttachWeapon(Weapon.Key, EAttachType::E_Handle);
		}
	}
}

void UWeaponComponent::DoMainAction()
{
}

void UWeaponComponent::EndMainAction()
{
}

void UWeaponComponent::DoSubAction()
{
}

void UWeaponComponent::EndSubAction()
{
}

void UWeaponComponent::DoAvoidAction()
{
}

void UWeaponComponent::EndAvoidAction()
{
}

void UWeaponComponent::DoReloadAction()
{
}

void UWeaponComponent::EquipWeapon(EWeaponSlot Slot)
{
	if (Slot == SelectedWeaponSlot) return;

	// 1. �ִϸ��̼� ����� ���� �� ����
	Swapping = true;

	// 2. ABP�� �Ѱ��ִ� ���� Ÿ�� �� ����
	CurrentWeaponType = GetAsset(Slot)->WeaponType;
}

void UWeaponComponent::AttachWeapon(EWeaponSlot Slot, EAttachType AttachType)
{
	ABaseWeapon* Weapon = GetWeapon(Slot);

	UWeaponDataAsset* Asset = GetAsset(Slot);
	FName SocketName;

	switch (AttachType)
	{
	case EAttachType::E_Holder:
		SocketName = Asset->HolderSocketName;
		break;
		
	case EAttachType::E_Handle:
		SocketName = Asset->HandleSocketName;
		break;

	default: break;
	}

	Weapon->AttachToComponent
	(
		Owner->GetMesh(),
		FAttachmentTransformRules::KeepRelativeTransform,
		SocketName
	);
}

