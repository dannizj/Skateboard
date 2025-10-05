// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimInstance.h"
//#include "Components/CapsuleComponent.h"
#include "Characters/SB_PlayerCharacter.h"

// Sets default values
ASB_PlayerCharacter::ASB_PlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;


	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComp->SetupAttachment(SpringArmComp);


}

// Called when the game starts or when spawned
void ASB_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PC = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}

	DefaultFOV = CameraComp->FieldOfView;

}


// Called every frame
void ASB_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddMovementInput(GetActorForwardVector(), Speed);

	float TargetSpeed = CurrentTargetSpeed;
	float CurrentSpeed = GetCharacterMovement()->MaxWalkSpeed;

	float InterpSpeed = 5.0f;

	float NewSpeed = FMath::FInterpTo(CurrentSpeed, TargetSpeed, DeltaTime, InterpSpeed);
	GetCharacterMovement()->MaxWalkSpeed = FMath::FInterpTo(CurrentSpeed, TargetSpeed, DeltaTime, InterpSpeed);

}

// Called to bind functionality to input
void ASB_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInput->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &ASB_PlayerCharacter::MoveForward);
	EnhancedInput->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ASB_PlayerCharacter::Turn);

	EnhancedInput->BindAction(JumpAction, ETriggerEvent::Started, this, &ASB_PlayerCharacter::BegingJump);
	EnhancedInput->BindAction(JumpAction, ETriggerEvent::Completed, this, &ASB_PlayerCharacter::BegingJump);

}

void ASB_PlayerCharacter::MoveForward(const FInputActionValue& Value)
{
	AxisValue = Value.Get<float>();	
	
	if (AxisValue > 0 && !UpChangeVelocity)
	{
		UpChangeVelocity = true;
		IsRuning = true;
	}
	if (AxisValue < 0 && !DownChangeVelocity)
	{
		DownChangeVelocity = true;
	}
	
}


void ASB_PlayerCharacter::Turn(const FInputActionValue& Value)
{
	AddControllerYawInput(Value.Get<float>() / 2);
}

void ASB_PlayerCharacter::BegingJump()
{
 //	Jump();
}


FVector ASB_PlayerCharacter::GetPawnViewLocation() const
{
	if (CameraComp)
	{
		return CameraComp->GetComponentLocation();
	}

	return Super::GetPawnViewLocation();
}



void ASB_PlayerCharacter::SetSpeedLevel(int32 KickCount)
{
	switch (KickCount)
	{
	case 0: CurrentTargetSpeed = 0.0f; Speed = 0; break;
	case 1: CurrentTargetSpeed = 700.0f; Speed = 1; break;
	case 2: CurrentTargetSpeed = 1200.0f; Speed = 1; break;
	case 3: CurrentTargetSpeed = 1500.0f; Speed = 1; break;
	default: CurrentTargetSpeed = 600.0f; Speed = 1; break;
	}
}

void ASB_PlayerCharacter::OnAnimNotifyKick()
{
	if (UpChangeVelocity && LevelOfSpeed < 3)
	{
		LevelOfSpeed++;
		UpChangeVelocity = false;
	}
	else if (DownChangeVelocity && LevelOfSpeed > 0)
	{
		LevelOfSpeed--;
		DownChangeVelocity = false;
	}

	SetSpeedLevel(LevelOfSpeed);
}

int ASB_PlayerCharacter::GetScore()
{
	return Points;
}

void ASB_PlayerCharacter::SetScore(int value)
{
	Points += value;
}



