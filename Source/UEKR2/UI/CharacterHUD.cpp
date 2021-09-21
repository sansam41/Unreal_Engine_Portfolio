// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterHUD.h"
#include "../Player/PlayerCharacter.h"
#include "UEKR2/UEKR2GameInstance.h"

void UCharacterHUD::NativeConstruct()
{
	Super::NativeConstruct();

	m_characterPic = Cast<UImage>(GetWidgetFromName(TEXT("CharacterPic")));
	m_NameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Name")));
	m_HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
	m_MPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("MPBar")));

	if(m_NameDelegate.IsBound())
	{
		m_NameDelegate.Execute();
	}

	APlayerCharacter* Player = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	UUEKR2GameInstance* GameInst = Cast<UUEKR2GameInstance>(GetWorld()->GetGameInstance());

	if (GameInst)
	{
		SetName(GameInst->GetPlayerName());
	}
	
	
}
void UCharacterHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
}

