#include "Weapons/BaseWeapon.h"
#include "Helper.h"

#include "Actions/ActionEnum.h"
#include "Actions/BaseAction.h"
#include "Characters/BaseCharacter.h"

ABaseWeapon::ABaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	Body = Helper::CreateSceneComponent<USkeletalMeshComponent>(this, "Body");
}

void ABaseWeapon::CreateAction(EActionType Type, TSubclassOf<UBaseAction> ActionClass)
{
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

