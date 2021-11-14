// Fill out your copyright notice in the Description page of Project Settings.


#include "AuctionItemList.h"

#include "AuctionItemDataList.h"

void UAuctionItemList::NativeConstruct()
{
	Super::NativeConstruct();

	m_IconImage = Cast<UImage>(GetWidgetFromName(TEXT("ItemIcon")));
	m_NameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("NameText")));

}
void UAuctionItemList::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}


void UAuctionItemList::SetData(UObject* Data)
{
	UAuctionItemDataList* InvenData=Cast<UAuctionItemDataList>(Data);
	
	m_NameText->SetText(FText::FromString(InvenData->GetNameText()));
	
	UTexture2D* IconTexture = InvenData->GetIcon();

	if(IconTexture)
		m_IconImage->SetBrushFromTexture(IconTexture);
}
