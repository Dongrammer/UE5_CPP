#include "Characters/Hero.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Helper.h"

AHero::AHero()
{
	PrimaryActorTick.bCanEverTick = true;

	CreateCamera();
	
	GetMesh()->SetSkeletalMesh(Helper::GetAsset<USkeletalMesh>(L"/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Quinn.SKM_Quinn'"));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
}

void AHero::BeginPlay()
{
	Super::BeginPlay();
}

void AHero::Tick(float DeltaSecond)
{
	Super::Tick(DeltaSecond);
}

void AHero::SetupPlayerInputComponent(UInputComponent* PlayerInput)
{
}

void AHero::Move(const FInputActionValue& Value)
{
}

void AHero::Look(const FInputActionValue& Value)
{
}

void AHero::CreateCamera()
{
	CameraArm = CreateDefaultSubobject<USpringArmComponent>("Camera Arm");
	CameraArm->SetupAttachment(RootComponent);

	CameraArm->TargetArmLength = 400.0f;
	CameraArm->bUsePawnControlRotation = true;

	Camera = Helper::CreateComponent<UCameraComponent>(this, "Camera", CameraArm);
	Camera->bUsePawnControlRotation = false;
}
