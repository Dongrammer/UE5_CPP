#include "Characters/Hero.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Helper.h"
#include "Input/InputDataAsset.h"

DEFINE_LOG_CATEGORY(HeroLog);

AHero::AHero()
{
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = false;

	CreateCamera();
	
	GetMesh()->SetSkeletalMesh(Helper::GetAsset<USkeletalMesh>(L"/Game/Template/Mannequins/Meshes/SKM_Quinn.SKM_Quinn"));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	GetMesh()->SetAnimInstanceClass(Helper::GetClass<UAnimInstance>(L"/Game/Animation/ABP_Default"));
}

void AHero::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController != nullptr)
	{
		UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		if (SubSystem != nullptr)
			SubSystem->AddMappingContext(KeyMappingContext, 0);
	}
}

void AHero::Tick(float DeltaSecond)
{
	Super::Tick(DeltaSecond);
}

void AHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent == nullptr) return;
	MappingInputAsset(EnhancedInputComponent);
}

void AHero::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();	// 카메라 움직임 용 모든 축 회전값
		const FRotator YawRotation = FRotator(0, Rotation.Yaw, 0);	// 캐릭터 움직임 용 Y축 회전값

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AHero::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerPitchInput(LookAxisVector.Y);
		AddControllerYawInput(LookAxisVector.X);
	}
}

void AHero::SelectMainWeapon()
{
	MULTICAST_DELEGATE_BROADCAST(DMainWeaponSelect);
}

void AHero::SelectSecondaryWeapon()
{
	MULTICAST_DELEGATE_BROADCAST(DSecondaryWeaponSelect);
}

void AHero::SelectThrowableWeapon()
{
	MULTICAST_DELEGATE_BROADCAST(DThrowableWeaponSelect);
}

void AHero::ChooseWeaponByScroll(const FInputActionValue& Value)
{
	int InValue = Value.Get<float>();

	if (DScrollSelect.IsBound()) DScrollSelect.Broadcast(InValue);
}

void AHero::DoMainAction()
{
	MULTICAST_DELEGATE_BROADCAST(DDoMainAction);
}

void AHero::EndMainAction()
{
	MULTICAST_DELEGATE_BROADCAST(DEndMainAction);
}

void AHero::DoSubAction()
{
	MULTICAST_DELEGATE_BROADCAST(DDoSubAction);
}

void AHero::EndSubAction()
{
	MULTICAST_DELEGATE_BROADCAST(DEndSubAction);
}

void AHero::DoAvoid()
{
	MULTICAST_DELEGATE_BROADCAST(DDoAvoidAction);
}

void AHero::EndAvoid()
{
	MULTICAST_DELEGATE_BROADCAST(DEndAvoidAction);

}
void AHero::DoReloadAction()
{
	MULTICAST_DELEGATE_BROADCAST(DDoReloadAction);
}

void AHero::CreateCamera()
{
	CameraArm = CreateDefaultSubobject<USpringArmComponent>("Camera Arm");
	CameraArm->SetupAttachment(RootComponent);

	CameraArm->TargetArmLength = 400.0f;
	CameraArm->bUsePawnControlRotation = true;

	Camera = Helper::CreateSceneComponent<UCameraComponent>(this, "Camera", CameraArm);
	Camera->bUsePawnControlRotation = false;
}

void AHero::MappingInputAsset(UEnhancedInputComponent* Comp)
{
	if (!InputAsset)
	{
		UE_LOG(HeroLog, Log, TEXT("Input Asset is Null Check BP_Hero"));
		return;
	}
	
	// Actions
	MAPPING_CLICK(Comp, InputAsset->MainAction, AHero::DoMainAction, AHero::EndMainAction);
	MAPPING_CLICK(Comp, InputAsset->SubAction, AHero::DoSubAction, AHero::EndSubAction);
	MAPPING_CLICK(Comp, InputAsset->AvoidAction, AHero::DoAvoid, AHero::EndAvoid);

	MAPPING_TRIGGERED(Comp, InputAsset->ReloadAction, AHero::DoReloadAction);

	// Motion
	MAPPING_TRIGGERED(Comp, InputAsset->LookAction, AHero::Look);
	MAPPING_TRIGGERED(Comp, InputAsset->MoveAction, AHero::Move);

	// Select
	MAPPING_TRIGGERED(Comp, InputAsset->MainWeaponSelect, AHero::SelectMainWeapon);
	MAPPING_TRIGGERED(Comp, InputAsset->SecondaryWeaponSelect, AHero::SelectSecondaryWeapon);
	MAPPING_TRIGGERED(Comp, InputAsset->ThrowableWeaponSelect, AHero::SelectThrowableWeapon);
	MAPPING_TRIGGERED(Comp, InputAsset->ScrollWeaponSelect, AHero::ChooseWeaponByScroll);
}

