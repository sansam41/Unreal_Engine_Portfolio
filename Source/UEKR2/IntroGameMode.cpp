// Fill out your copyright notice in the Description page of Project Settings.


#include "IntroGameMode.h"

AIntroGameMode::AIntroGameMode() {


	static ConstructorHelpers::FClassFinder<UIntroWidget> IntroClass(TEXT("WidgetBlueprint'/Game/UI/UI_Intro.UI_Intro_C'"));
	if(IntroClass.Succeeded())
		m_IntroClass=IntroClass.Class;
}

void AIntroGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}
void AIntroGameMode::BeginPlay()
{
	Super::BeginPlay();
	if(IsValid(m_IntroClass))
	{
		m_IntroWidget=Cast<UIntroWidget>(CreateWidget(GetWorld(),
			m_IntroClass));

		if(m_IntroWidget)
			m_IntroWidget->AddToViewport();
	}

	APlayerController* Controller = GetWorld()->GetFirstPlayerController();

	FInputModeUIOnly	Mode;
	//FInputModeGameOnly : FPS게임
	//FInputModeGameAndUI : 롤같은 게임

	Controller->SetInputMode(Mode);
	Controller->bShowMouseCursor = true;
	
}