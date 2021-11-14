// Fill out your copyright notice in the Description page of Project Settings.


#include "IntroWidget.h"


void UIntroWidget::NativeConstruct()
{
	Super::NativeConstruct();


	m_Screen = Cast<UImage>(GetWidgetFromName(TEXT("Screen")));
	m_DescText = Cast<UTextBlock>(GetWidgetFromName(TEXT("DescText")));


}
void UIntroWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}