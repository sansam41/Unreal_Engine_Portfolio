// Fill out your copyright notice in the Description page of Project Settings.


#include "NpcInfoBar.h"


void UNpcInfoBar::NativeConstruct()
{
	Super::NativeConstruct();
	
	m_NameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Name")));

	if(m_NameDelegate.IsBound())
	{
		m_NameDelegate.Execute();
	}
}

void UNpcInfoBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}