// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItemList.h"
#include "InventoryItemDataList.h"


void UInventoryItemList::NativeConstruct()
{
	Super::NativeConstruct();

	m_IconImage = Cast<UImage>(GetWidgetFromName(TEXT("ItemIcon")));
	m_NameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("NameText")));

}
void UInventoryItemList::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}


void UInventoryItemList::SetData(UObject* Data)
{
	UInventoryItemDataList* InvenData=Cast<UInventoryItemDataList>(Data);
	
	m_NameText->SetText(FText::FromString(InvenData->GetNameText()));
	
	UTexture2D* IconTexture = InvenData->GetIcon();

	if(IconTexture)
		m_IconImage->SetBrushFromTexture(IconTexture);
}
