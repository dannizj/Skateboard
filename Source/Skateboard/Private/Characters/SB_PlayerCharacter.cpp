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
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//create camera and spring
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
	// Added mapping context by scripting
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


}

// Called to bind functionality to input
void ASB_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInput->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &ASB_PlayerCharacter::MoveForward);
	EnhancedInput->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ASB_PlayerCharacter::Turn);
	EnhancedInput->BindAction(JumpAction, ETriggerEvent::Started, this, &ASB_PlayerCharacter::Jump);

}

void ASB_PlayerCharacter::MoveForward(const FInputActionValue& Value)
{
	float AxisValue = Value.Get<float>();
	AddMovementInput(GetActorForwardVector(), AxisValue);
}


void ASB_PlayerCharacter::Turn(const FInputActionValue& Value)
{
	AddControllerYawInput(Value.Get<float>() / 2);
}


FVector ASB_PlayerCharacter::GetPawnViewLocation() const
{
	if (CameraComp)
	{
		return CameraComp->GetComponentLocation();
	}

	return Super::GetPawnViewLocation();
}



