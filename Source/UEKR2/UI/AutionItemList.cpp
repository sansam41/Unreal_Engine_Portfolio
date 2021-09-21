// Fill out your copyright notice in the Description page of Project Settings.


#include "AutionItemList.h"

#include "AuctionItemDataList.h"


void UAutionItemList::NativeConstruct()
{
	Super::NativeConstruct();

	m_IconImage = Cast<UImage>(GetWidgetFromName(TEXT("ItemIcon")));
	m_NameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("NameText")));

}
void UAutionItemList::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}


void UAutionItemList::SetData(UObject* Data)
{
	UAuctionItemDataList* InvenData=Cast<UAuctionItemDataList>(Data);
	
	m_NameText->SetText(FText::FromString(InvenData->GetNameText()));
	
	UTexture2D* IconTexture = LoadObject<UTexture2D>(nullptr,*InvenData->GetIconPath());

	if(IconTexture)
		m_IconImage->SetBrushFromTexture(IconTexture);
}
