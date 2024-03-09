#include "Weapons/BaseWeapon.h"
#include "Helper.h"
ABaseWeapon::ABaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	Body = Helper::CreateComponent<USkeletalMeshComponent>(this, "Body");
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

