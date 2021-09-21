// Fill out your copyright notice in the Description page of Project Settings.


#include "HPBar.h"

void UHPBar::NativeConstruct()
{
	Super::NativeConstruct();


	m_HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("Bar")));
	m_NameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Name")));

	if(m_NameDelegate.IsBound())
	{
		m_NameDelegate.Execute();
	}
}
void UHPBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}