#include "Components/WeaponComponent.h"
#include "Weapons/WeaponEnum.h"
#include "Weapons/BaseWeapon.h"
#include "Characters/BaseCharacter.h"
#include "Weapons/WeaponDataAsset.h"
#include "Characters/Hero.h"
#include "Actions/BaseAction.h"
#include "Actions/ActionEnum.h"

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
			for (auto& Action : Weapon.Value->Actions)
				Temp->CreateAction(Action.Key, Action.Value);

			Weapons.Add(Weapon.Key, Temp);
			AttachWeapon(Weapon.Key, EAttachType::E_Handle);
		}
	}

	CurrentWeapon = GetWeapon(EWeaponSlot::E_Main);
}

void UWeaponComponent::DoMainAction()
{
	CurrentWeapon->GetAction(EActionType::MainAction)->DoAction();
}

void UWeaponComponent::EndMainAction()
{
	CurrentWeapon->GetAction(EActionType::MainAction)->EndAction();
}

void UWeaponComponent::DoSubAction()
{
	CurrentWeapon->GetAction(EActionType::SubAction)->DoAction();
}

void UWeaponComponent::EndSubAction()
{
	CurrentWeapon->GetAction(EActionType::SubAction)->EndAction();
}

void UWeaponComponent::DoAvoidAction()
{
	CurrentWeapon->GetAction(EActionType::AvoidAction)->DoAction();
}

void UWeaponComponent::EndAvoidAction()
{
	CurrentWeapon->GetAction(EActionType::AvoidAction)->EndAction();
}

void UWeaponComponent::DoReloadAction()
{
	CurrentWeapon->GetAction(EActionType::ReloadAction)->DoAction();
}

void UWeaponComponent::EquipWeapon(EWeaponSlot Slot)
{
	if (Slot == SelectedWeaponSlot) return;

	// 1. 애니메이션 재생을 위한 값 변경
	Swapping = true;

	// 2. ABP에 넘겨주는 무기 타입 값 수정
	CurrentWeaponType = GetAsset(Slot)->WeaponType;
	
	// 현재 무기
	CurrentWeapon = GetWeapon(Slot);
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

