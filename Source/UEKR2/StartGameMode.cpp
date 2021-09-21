// Fill out your copyright notice in the Description page of Project Settings.


#include "StartGameMode.h"

AStartGameMode::AStartGameMode() {


	static ConstructorHelpers::FClassFinder<UStartWidget> StartHUDClass(TEXT("WidgetBlueprint'/Game/UI/UI_Start.UI_Start_C'"));
	if(StartHUDClass.Succeeded())
		m_StartWidgetClass=StartHUDClass.Class;
}

void AStartGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}
void AStartGameMode::BeginPlay()
{
	Super::BeginPlay();
	if(IsValid(m_StartWidgetClass))
	{
		m_StartWidgetHUD=Cast<UStartWidget>(CreateWidget(GetWorld(),
			m_StartWidgetClass));

		if(m_StartWidgetHUD)
			m_StartWidgetHUD->AddToViewport();
	}

	APlayerController* Controller = GetWorld()->GetFirstPlayerController();

	FInputModeUIOnly	Mode;
	//FInputModeGameOnly : FPS게임
	//FInputModeGameAndUI : 롤같은 게임

	Controller->SetInputMode(Mode);
	Controller->bShowMouseCursor = true;
	
}