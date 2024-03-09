#include "Characters/Hero.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Helper.h"

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

	if (EnhancedInputComponent != nullptr)
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHero::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AHero::Look);
	}
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

void AHero::CreateCamera()
{
	CameraArm = CreateDefaultSubobject<USpringArmComponent>("Camera Arm");
	CameraArm->SetupAttachment(RootComponent);

	CameraArm->TargetArmLength = 400.0f;
	CameraArm->bUsePawnControlRotation = true;

	Camera = Helper::CreateComponent<UCameraComponent>(this, "Camera", CameraArm);
	Camera->bUsePawnControlRotation = false;
}
