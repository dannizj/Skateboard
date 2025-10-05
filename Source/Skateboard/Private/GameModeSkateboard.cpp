// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeSkateboard.h"
#include "UI/CharacterHUD.h"

AGameModeSkateboard::AGameModeSkateboard()
{
	HUDClass = ACharacterHUD::StaticClass();
}
