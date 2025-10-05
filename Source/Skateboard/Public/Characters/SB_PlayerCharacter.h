// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "SB_PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;


UCLASS()
class SKATEBOARD_API ASB_PlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASB_PlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "InputMappingContext")
	UInputMappingContext* InputMappingContext = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveForwardAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* TurnAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction = nullptr;


	void MoveForward(const FInputActionValue& Value);
	void Turn(const FInputActionValue& Value);
	void BegingJump();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	float DefaultFOV;

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	bool IsRuning;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	int LevelOfSpeed;
	float AxisValue;

	float CurrentTargetSpeed;
	bool UpChangeVelocity;
	bool DownChangeVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	int Points;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual FVector GetPawnViewLocation() const override;

	void SetSpeedLevel(int32 KickCount);

	UFUNCTION(BlueprintCallable)
	void OnAnimNotifyKick();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	bool IsJumping;

	

	int GetScore();
	void SetScore(int value);

};
