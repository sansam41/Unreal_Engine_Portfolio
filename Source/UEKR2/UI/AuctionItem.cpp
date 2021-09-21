// Fill out your copyright notice in the Description page of Project Settings.


#include "AuctionItem.h"
#include "AuctionItemData.h"
#include "Components/CanvasPanelSlot.h"

void UAuctionItem::NativeConstruct()
{
	Super::NativeConstruct();

	m_NameText= Cast<UTextBlock>(GetWidgetFromName(TEXT("NameText")));
	m_Selection= Cast<UImage>(GetWidgetFromName(TEXT("Selection")));
	
	
}
void UAuctionItem::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UAuctionItem::SetData(UObject* Data)
{
	UAuctionItemData* Item=Cast<UAuctionItemData>(Data);

	Item->SetLinkItem(this);
	
	m_NameText->SetText(FText::FromString(Item->GetNameText()));
	
	UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(m_NameText->Slot);

	if(PanelSlot)
		PanelSlot->SetPosition(FVector2D(Item->GetTreeLevel()*50.f,0.f));

	
	PanelSlot = Cast<UCanvasPanelSlot>(m_Selection->Slot);

	if(PanelSlot)
		PanelSlot->SetPosition(FVector2D(Item->GetTreeLevel()*50.f,0.f));
}

void UAuctionItem::Selection()
{
	m_Selection->SetOpacity(0.3f);
}
void UAuctionItem::UnSelection()
{
	m_Selection->SetOpacity(0.f);
}