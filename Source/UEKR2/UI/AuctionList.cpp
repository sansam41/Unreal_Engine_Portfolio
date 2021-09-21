// Fill out your copyright notice in the Description page of Project Settings.


#include "AuctionList.h"

#include "AuctionItemDataList.h"
#include "UEKR2/UEKR2GameInstance.h"


void UAuctionList::NativeConstruct()
{
	Super::NativeConstruct();

	m_AuctionList = Cast<UListView>(GetWidgetFromName(TEXT("InventoryList")));
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
		UAuctionItemDataList* Data=NewObject<UAuctionItemDataList>(this,UAuctionItemDataList::StaticClass());

		
		Data->SetNameText(Info->Name);
		Data->SetIconPath(Info->IconPath);
		Data->SetType(Info->Type,Info->Type);
		
		
		Data->SetIndex(i);

		m_ItemArray.Push(Data);
		//m_AuctionList->AddItem(Data);
	}

	// 클릭했을 때 동작할 함수를 등록한다.
	m_AuctionList->OnItemClicked().AddUObject(this,&UAuctionList::ItemClick);
	//m_InventoryList->OnItemSelectionChanged()
	//m_InventoryList->OnItemDoubleClicked()
	//m_InventoryList->OnItemIsHoveredChanged()
	
}
void UAuctionList::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UAuctionList::SetAuctionList(FString Name)
{
	UUEKR2GameInstance* GameInst=Cast<UUEKR2GameInstance>(GetWorld()->GetGameInstance());
	PrintViewport(1.f,FColor::Red,Name);
	//const FUIItemTableInfo* Info=GameInst->FindUIItemInfo(Name);
	m_AuctionList->ClearListItems();
	for(auto it : m_ItemArray)
	{

		if(it->GetType()==Name)
			m_AuctionList->AddItem(it);
	}
	
}


void UAuctionList::ItemClick(UObject* Data)
{
	UAuctionItemDataList* Item = Cast<UAuctionItemDataList>(Data);

	if(Item)
	{
		m_AuctionList->RemoveItem(Data);
		m_ItemArray.RemoveAt(Item->GetIndex());
		PrintViewport(1.f,FColor::Red,Item->GetNameText());
	}
	
}
