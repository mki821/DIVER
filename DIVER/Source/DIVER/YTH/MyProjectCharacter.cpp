#include "MyProjectCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"	
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Engine/OverlapResult.h"
#include "Minki/Interface/DamageableInterface.h"


//////////////////////////////////////////////////////////////////////////

AMyProjectCharacter::AMyProjectCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// // // Create a camera boom (pulls in towards the player if there is a collision)
	// CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	// CameraBoom->SetupAttachment(RootComponent);
	// CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	// CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(GetMesh(), TEXT("head"));
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm


	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}


void AMyProjectCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

void AMyProjectCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!isBreathing)
	{
		CurrentOxygen -= OxygenDecrementRate * DeltaTime;
		CurrentOxygen = FMath::Max(CurrentOxygen, 0.0f);
		if (CurrentOxygen <= 0.0f)
		{
			// 사망처리나 피깍아야됨
		}
	}

	if (CurrentOxygen <= MaxOxygen && isBreathing)
	{
		CurrentOxygen += OxygenIncrementRate * DeltaTime;
		CurrentOxygen = FMath::Min(CurrentOxygen, MaxOxygen);
	}
}

void AMyProjectCharacter::ShockwaveAttack()
{
	if (!bCanAttack) return;
    
	// 쿨다운 시작
	bCanAttack = false;
	GetWorldTimerManager().SetTimer(AttackCooldownTimer, this, &AMyProjectCharacter::ResetAttack, AttackCooldown);
    
	// 1. 나이아가라 이펙트 재생
	if (ShockwaveEffect)
	{
		UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(),
			ShockwaveEffect,
			GetActorLocation(),
			GetActorRotation()
		);
        
		if (NiagaraComp)
		{
			NiagaraComp->SetNiagaraVariableFloat(FString("User.EffectScale"), AttackRange / 500.0f);
		}
	}

	TArray<FOverlapResult> OverlapResults;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(AttackRange);
    
	bool bHit = GetWorld()->OverlapMultiByChannel(
		OverlapResults,
		GetActorLocation(),
		FQuat::Identity,
		ECC_GameTraceChannel1, 
		Sphere
	);
    
	for (const FOverlapResult& Result : OverlapResults)
	{
		AActor* HitActor = Result.GetActor();
		if (IDamageableInterface* Damageable = Cast<IDamageableInterface>(HitActor))
		{
			Damageable->TakeDamage(AttackDamage);
		}
	}
}

void AMyProjectCharacter::ResetAttack()
{
	bCanAttack = true;
}


//////////////////////////////////////////////////////////////////////////
// Input

void AMyProjectCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyProjectCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyProjectCharacter::Look);
	}
}

void AMyProjectCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (isSwimming)
	{
		if (Controller != nullptr)
		{
			const FRotator ControlRotation = Controller->GetControlRotation();

			FVector CameraForward = FRotationMatrix(ControlRotation).GetUnitAxis(EAxis::X);

			float ForwardInput = MovementVector.Y; // W/S 입력 (Y축)
			
			if (ForwardInput > 0) // W키를 누를 때만
			{
				FVector MoveDirection = CameraForward * ForwardInput;

				FVector CurrentLocation = GetActorLocation();
				bool bIsAtTop = CurrentLocation.Z >= 9600.0f;

				if (bIsAtTop && MoveDirection.Z > 0)
				{
					MoveDirection.Z = 0;
					if (!MoveDirection.IsNearlyZero())
					{
						MoveDirection.Normalize();
					}
				}

				AddMovementInput(MoveDirection, 1.0f);
			}
		}
	}
	else
	{
		if (Controller != nullptr)
		{
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);
	
			const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
			FVector MoveDirection = (ForwardDirection * MovementVector.Y) + (RightDirection * MovementVector.X);
	
			if (!MoveDirection.IsNearlyZero())
			{
				MoveDirection.Normalize();
	
				AddMovementInput(MoveDirection, 1.0f);
	
				FRotator TargetRotation = MoveDirection.Rotation();
				FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation,
														GetWorld()->GetDeltaSeconds(), 8.0f);
				SetActorRotation(NewRotation);
			}
		}
	}
}


void AMyProjectCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		float MouseSensitivity = 0.5f;
		FRotator CurrentRotation = Controller->GetControlRotation();
		float NewPitch = CurrentRotation.Pitch - (LookAxisVector.Y * MouseSensitivity);
		NewPitch = FMath::Clamp(NewPitch, -75.0f, 75.0f);

		float CharacterYaw = GetActorRotation().Yaw;

		float NewYaw = CurrentRotation.Yaw + (LookAxisVector.X * MouseSensitivity);

		float MinYaw = CharacterYaw - 50.0f;
		float MaxYaw = CharacterYaw + 50.0f;
		NewYaw = FMath::ClampAngle(NewYaw, MinYaw, MaxYaw);

		FRotator NewRotation = FRotator(NewPitch, NewYaw, 0.0f);
		Controller->SetControlRotation(NewRotation);
	}
}
