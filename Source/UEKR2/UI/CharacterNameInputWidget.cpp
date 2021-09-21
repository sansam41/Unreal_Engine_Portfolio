// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterNameInputWidget.h"
#include "../Player/PlayerCharacter.h"

void UCharacterNameInputWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_InputText = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("InputText")));

	
	
}
void UCharacterNameInputWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

