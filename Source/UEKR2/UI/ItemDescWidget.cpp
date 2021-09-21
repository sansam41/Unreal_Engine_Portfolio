// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemDescWidget.h"

void UItemDescWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_IconImage= Cast<UImage>(GetWidgetFromName(TEXT("Icon")));
	m_NameText= Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemName")));
	
	
}
void UItemDescWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}
