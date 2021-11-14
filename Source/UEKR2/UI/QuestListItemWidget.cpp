// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestListItemWidget.h"


void UQuestListItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_NameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("NameText")));
	m_Selection = Cast<UImage>(GetWidgetFromName(TEXT("Selection")));

	m_Select=false;
	
}

void UQuestListItemWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}


void UQuestListItemWidget::SetData(UObject* Data)
{
	UQuestListItemData* Item = Cast<UQuestListItemData>(Data);

	Item->SetOwnerWidger(this);
	
	m_NameText->SetText(FText::FromString(Item->GetQuestName()));
}

void UQuestListItemWidget::Select(bool Enable)
{
	m_Select=Enable;
	if(Enable)
	{
		FLinearColor color(1.2f,0.7f,0.f,0.5f);
		m_Selection->SetBrushTintColor(color);
	}
	else
	{
		
		FLinearColor color(0.2f,0.2f,0.2f,0.f);
		m_Selection->SetBrushTintColor(color);
	}
}
void UQuestListItemWidget::MouseOn(bool Enable)
{
	
	if(!m_Select)
	{
		if(Enable)
		{
			FLinearColor color(0.2f,0.2f,0.2f,0.5f);
			m_Selection->SetBrushTintColor(color);
		}
		else
		{
		
			FLinearColor color(0.2f,0.2f,0.2f,0.f);
			m_Selection->SetBrushTintColor(color);
		}
	}
}