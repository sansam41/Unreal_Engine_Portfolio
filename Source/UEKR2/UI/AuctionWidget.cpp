// Fill out your copyright notice in the Description page of Project Settings.


#include "AuctionWidget.h"

#include "AuctionItemData.h"
#include "UEKR2/UEKR2GameInstance.h"

void UAuctionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_SelectionItem=nullptr;

	m_Menu= Cast<UTreeView>(GetWidgetFromName(TEXT("Tree")));
	m_AuctionList=Cast<UAuctionList>(GetWidgetFromName(TEXT("UI_AuctionList")));
	
	m_Menu->OnItemClicked().AddUObject(this,&UAuctionWidget::ItemClick);
	m_Menu->OnItemIsHoveredChanged().AddUObject(this,&UAuctionWidget::ItemHovered); // 어떤 아이템에 마우스가 올라갔는지
	
	m_Menu->SetOnGetItemChildren(this,&UAuctionWidget::GetItemChildren);


	UAuctionItemData* Data=NewObject<UAuctionItemData>(this,UAuctionItemData::StaticClass());

	Data->SetNameText(TEXT("무기"));

	Data->CreateChildren(TEXT("검"));
	Data->CreateChildren(TEXT("활"));
	Data->CreateChildren(TEXT("총"));
	Data->CreateChildren(TEXT("지팡이"));
	
	m_Menu->AddItem(Data);


	Data=NewObject<UAuctionItemData>(this,UAuctionItemData::StaticClass());

	Data->SetNameText(TEXT("방어구"));

	Data->CreateChildren(TEXT("갑옷"));
	Data->CreateChildren(TEXT("투구"));
	Data->CreateChildren(TEXT("신발"));
	Data->CreateChildren(TEXT("장갑"));
	m_Menu->AddItem(Data);




	Data=NewObject<UAuctionItemData>(this,UAuctionItemData::StaticClass());
	Data->SetNameText(TEXT("포션"));
	
	Data->CreateChildren(TEXT("체력"));
	Data->CreateChildren(TEXT("마나"));
		
	m_Menu->AddItem(Data);
	
	/*
	FString ItemNameArray[4]=
	{
		TEXT("BF대검"),
		TEXT("칠흑의양날도끼"),
		TEXT("HP포션"),
		TEXT("MP포션")
	};

	UUEKR2GameInstance* GameInst=Cast<UUEKR2GameInstance>(GetWorld()->GetGameInstance());
	
	for(int32 i=0;i<100;i++)
	{
		int32	Index=FMath::RandRange(0, 3);

		const FUIItemTableInfo* Info=GameInst->FindUIItemInfo(ItemNameArray[Index]);

		UInventoryItemDataList* Data=NewObject<UInventoryItemDataList>(this,UInventoryItemDataList::StaticClass());

		Data->SetNameText(Info->Name);
		Data->SetIconPath(Info->IconPath);
		Data->SetIndex(i);
		
		m_InventoryList->AddItem(Data);
	}
	*/
	
}
void UAuctionWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}


FReply UAuctionWidget::NativeOnMouseMove(const FGeometry& InGeometry, 
	const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseMove(InGeometry, InMouseEvent);
	

	return FReply::Handled();
}

void UAuctionWidget::ItemClick(UObject* Data)
{
	if(m_SelectionItem)
		m_SelectionItem->UnSelection();
	m_SelectionItem = Cast<UAuctionItemData>(Data);

	m_AuctionList->SetAuctionList(m_SelectionItem->GetNameText());
}

void UAuctionWidget::ItemHovered(UObject* Data,bool Hovered)
{
	UAuctionItemData* Item=Cast<UAuctionItemData>(Data);
	if(Hovered)
	{
		Item->Selection();
	}
	else if(m_SelectionItem!=Item)
	{
		
		Item->UnSelection();
	}
}

void UAuctionWidget::GetItemChildren(UObject* Data,TArray<UObject*>& ItemArray)
{
	UAuctionItemData* Item = Cast<UAuctionItemData>(Data);

	if(Item)
		ItemArray = Item->GetChildArray();
}