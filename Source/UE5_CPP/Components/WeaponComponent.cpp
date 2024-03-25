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
	CurrentWeaponSlot = EWeaponSlot::E_Main;
	CurrentWeaponType = GetAsset(CurrentWeaponSlot)->WeaponType;

	if (AHero* Hero = Cast<AHero>(Owner))
	{
		Hero->DDoMainAction.AddUFunction(this, "DoMainAction");
		Hero->DEndMainAction.AddUFunction(this, "EndMainAction");

		Hero->DDoSubAction.AddUFunction(this, "DoSubAction");
		Hero->DEndSubAction.AddUFunction(this, "EndSubAction");

		Hero->DDoAvoidAction.AddUFunction(this, "DoAvoidAction");
		Hero->DEndAvoidAction.AddUFunction(this, "EndAvoidAction");

		Hero->DDoReloadAction.AddUFunction(this, "DoReloadAction");

		// Select Weapon Delegate
		Hero->DMainWeaponSelect.AddUFunction(this, "SelectMainWeapon");
		Hero->DSecondaryWeaponSelect.AddUFunction(this, "SelectSecondaryWeapon");
		Hero->DScrollSelect.AddUFunction(this, "ChooseWeaponByScroll");
	}
}

void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CALL_ACTION(EActionType::MainAction, EActionTiming::Tick);
	CALL_ACTION(EActionType::SubAction, EActionTiming::Tick);
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
			AttachWeapon(Weapon.Key, EAttachType::E_Holder);
		}
	}

	// 임시로 손에 들고 있게 하기 위해서 작성
	CurrentWeapon = GetWeapon(EWeaponSlot::E_Main);
	AttachWeapon(EWeaponSlot::E_Main, EAttachType::E_Handle);
}

void UWeaponComponent::DoMainAction()
{
	CALL_ACTION(EActionType::MainAction, EActionTiming::Do);
}

void UWeaponComponent::EndMainAction()
{
	CALL_ACTION(EActionType::MainAction, EActionTiming::End);
}

void UWeaponComponent::DoSubAction()
{
	CALL_ACTION(EActionType::SubAction, EActionTiming::Do);
}

void UWeaponComponent::EndSubAction()
{
	CALL_ACTION(EActionType::SubAction, EActionTiming::End);
}

void UWeaponComponent::DoAvoidAction()
{
	CALL_ACTION(EActionType::AvoidAction, EActionTiming::Do);
}

void UWeaponComponent::EndAvoidAction()
{
	CALL_ACTION(EActionType::AvoidAction, EActionTiming::End);
}

void UWeaponComponent::DoReloadAction()
{
	CALL_ACTION(EActionType::ReloadAction, EActionTiming::Do);
}

void UWeaponComponent::SelectMainWeapon()
{
	EquipWeapon(EWeaponSlot::E_Main);
}

void UWeaponComponent::SelectSecondaryWeapon()
{
	EquipWeapon(EWeaponSlot::E_Second);
}

void UWeaponComponent::SelectThrowableWeapon()
{
	EquipWeapon(EWeaponSlot::E_Throwable);
}

void UWeaponComponent::ChooseWeaponByScroll(uint8 InValue)
{
}

void UWeaponComponent::EquipWeapon(EWeaponSlot Slot)
{
	if (Slot == CurrentWeaponSlot || bSwapping == true) return;

	// ABP 값 변경
	bSwapping = true;
	CurrentWeaponType = GetAsset(Slot)->WeaponType;

	// 무기 부착
	AttachWeapon(CurrentWeaponSlot, EAttachType::E_Holder);
	CurrentWeapon = GetWeapon(Slot);
	CurrentWeaponSlot = Slot;
	AttachWeapon(CurrentWeaponSlot, EAttachType::E_Handle);
}

void UWeaponComponent::AttachWeapon(EWeaponSlot Slot, EAttachType AttachType)
{
	ABaseWeapon* Weapon = GetWeapon(Slot);
	UWeaponDataAsset* Asset = GetAsset(Slot);

	if (!Asset) return;
	
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

