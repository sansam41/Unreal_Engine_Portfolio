// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryList.h"
#include "../UEKR2GameInstance.h"
#include "InventoryItemDataList.h"
#include "UEKR2/UEKR2GameModeBase.h"

void UInventoryList::NativeConstruct()
{
	Super::NativeConstruct();

	m_InventoryList = Cast<UListView>(GetWidgetFromName(TEXT("InventoryList")));
	m_GoldText = Cast<UTextBlock>(GetWidgetFromName(TEXT("GoldText")));
	if(m_InventoryInitDelegate.IsBound())
		m_InventoryInitDelegate.Execute();

	// 클릭했을 때 동작할 함수를 등록한다.
	m_InventoryList->OnItemClicked().AddUObject(this,&UInventoryList::ItemClick);
	//m_InventoryList->OnItemSelectionChanged()
	//m_InventoryList->OnItemDoubleClicked()
	//m_InventoryList->OnItemIsHoveredChanged()


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
	Data->SetIcon(Info->IconTexture);
	Data->SetIndex(i);
		
	m_InventoryList->AddItem(Data);
	}
	*/
	
}
void UInventoryList::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UInventoryList::ItemClick(UObject* Data)
{
	UInventoryItemDataList* Item = Cast<UInventoryItemDataList>(Data);
	AUEKR2GameModeBase* GameMode = Cast<AUEKR2GameModeBase>(GetWorld()->GetAuthGameMode());
	if(Item)
	{
		m_InventoryList->RemoveItem(Data);
		PrintViewport(1.f,FColor::Red,Item->GetNameText());
	}
	
}



void UInventoryList::AddItem(const FUIItemTableInfo* ItemInfo)
{
	UInventoryItemDataList* Data=NewObject<UInventoryItemDataList>(this,UInventoryItemDataList::StaticClass());

	Data->SetNameText(ItemInfo->Name);
	Data->SetIcon(ItemInfo->IconTexture);
	Data->SetIndex(m_InventoryList->GetNumItems());
		
	m_InventoryList->AddItem(Data);
}
bool UInventoryList::FindItem(const FString& ItemName)
{
	TArray<UObject*> Items = m_InventoryList->GetListItems();
	for(auto& it : Items)
	{
		UInventoryItemDataList* Item = Cast<UInventoryItemDataList>(it);
		if(Item->GetNameText()==ItemName)
			return true;
	}
	return false;
}



void UInventoryList::SetGold(int32 Gold)
{
	m_GoldText->SetText(FText::FromString(FString::FromInt(Gold)));
}
