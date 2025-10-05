// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CharacterHUD.h"
#include "Engine/Canvas.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"
#include "Characters/SB_PlayerCharacter.h"

void ACharacterHUD::DrawHUD()
{
	Super::DrawHUD();

	APlayerController* PC = GetOwningPlayerController();
	if (!PC) return;

	ASB_PlayerCharacter* Character = Cast<ASB_PlayerCharacter>(PC->GetPawn());
	if (!Character) return;

	const float Score = Character->GetScore();

	FString ScoreText = FString::Printf(TEXT("Score: %d"), FMath::RoundToInt(Score));

	int32 SizeX = 0;
	int32 SizeY = 0;
	PC->GetViewportSize(SizeX, SizeY);


	DrawText(
		ScoreText,
		FLinearColor::Yellow,
		SizeX * 0.4f,
		SizeY * 0.05f,
		GEngine->GetLargeFont(),
		3.0f
	);
}
