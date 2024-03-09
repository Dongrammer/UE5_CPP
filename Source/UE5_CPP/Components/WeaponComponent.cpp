#include "Components/WeaponComponent.h"
#include "Weapons/WeaponEnum.h"
#include "Weapons/BaseWeapon.h"
#include "Characters/BaseCharacter.h"

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ABaseCharacter>(GetOwner());

	SpawnWeapons();
}

void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UWeaponComponent::SpawnWeapons()
{
	/*for (auto& Weapon : WeaponAssets)
	{
		if (!Weapon.Value) return;

		FActorSpawnParameters SpawnParameter;
		SpawnParameter.Owner = GetOwner();

		ABaseWeapon* Temp = Cast<ABaseWeapon>(GetOwner()->GetWorld()->SpawnActor<AActor>(Weapon.Value, FVector(), FRotator(), SpawnParameter));

		if (Temp)
		{
			Weapons.Add(Weapon.Key, Temp);
			Temp->AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "Rifle_Holder");
		}
	}*/
}

void UWeaponComponent::EquipWeapon(EWeaponSlot Slot)
{
}

void UWeaponComponent::AttachWeapon(EWeaponSlot Slot, EAttachType AttachType)
{
	
}

