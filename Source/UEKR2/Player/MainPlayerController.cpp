// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"

AMainPlayerController::AMainPlayerController()
{
	bShowMouseCursor=true;
	m_ShowUI=false;
}
void AMainPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

}