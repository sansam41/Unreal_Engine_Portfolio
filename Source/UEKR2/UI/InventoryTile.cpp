// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryTile.h"

#include "InventoryTileData.h"
#include "../UEKR2GameInstance.h"
#include "Components/CanvasPanelSlot.h"

void UInventoryTile::NativeConstruct()
{
	Super::NativeConstruct();
	m_ItemCount=0;

	m_InventoryTile= Cast<UTileView>(GetWidgetFromName(TEXT("InventoryTile")));
	m_InventorySlot= Cast<UTileView>(GetWidgetFromName(TEXT("InventorySlot")));
	m_ItemDescWidget= Cast<UItemDescWidget>(GetWidgetFromName(TEXT("UI_ItemDesc")));

	m_InventoryTile->SetScrollbarVisibility(ESlateVisibility::Collapsed);
	m_InventorySlot->SetScrollbarVisibility(ESlateVisibility::Collapsed);
	
	FString ItemNameArray[4]=
	{
		TEXT("BF대검"),
		TEXT("칠흑의양날도끼"),
		TEXT("HP포션"),
		TEXT("MP포션")
	};
	// 슬롯은 무조건 20개 유지
	for(int i=0;i<20;i++)
	{
		UInventoryTileData* Data=NewObject<UInventoryTileData>(this,UInventoryTileData::StaticClass());
		m_InventorySlot->AddItem(Data);
		m_SlotArray.Add(Data);
	}
	/*
	UUEKR2GameInstance* GameInst=Cast<UUEKR2GameInstance>(GetWorld()->GetGameInstance());

	
	for (int32 i = 0; i < 100; ++i)
	{
		int32	Index = FMath::RandRange(0, 2);

		const FUIItemTableInfo* Info = GameInst->FindUIItemInfo(ItemNameArray[Index]);

		UInventoryItemDataTile* Data = NewObject<UInventoryItemDataTile>(this,
		UInventoryItemDataTile::StaticClass());

		Data->SetIcon(Info->IconTexture);
		Data->SetIndex(i);
		Data->SetNameText(Info->Name);

		m_InventoryTile->AddItem(Data);

		if (i >= 20)
		{
			UInventoryTileData* Data1 = NewObject<UInventoryTileData>(this, UInventoryTileData::StaticClass());

			m_InventorySlot->AddItem(Data1);

			m_SlotArray.Add(Data1);
		}
	}
	*/
	m_ItemCount=100;

	m_InventoryTile->OnItemClicked().AddUObject(this, &UInventoryTile::ItemClick);
	//m_InventoryTile->OnItemScrolledIntoView().AddUObject(this,&UInventoryTile::ItemScroll);
	// 클릭했을 때 동작할 함수를 등록한다.
	//m_InventoryList->OnItemClicked().AddUObject(this,&UInventoryList::ItemClick);
	//m_InventoryList->OnItemSelectionChanged()
	//m_InventoryList->OnItemDoubleClicked()
	m_InventoryTile->OnItemIsHoveredChanged().AddUObject(this,&UInventoryTile::ItemHovered); // 어떤 아이템에 마우스가 올라갔는지 
	
}




void UInventoryTile::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}


FReply UInventoryTile::NativeOnMouseMove(const FGeometry& InGeometry, 
	const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseMove(InGeometry, InMouseEvent);

	if (m_MouseHovered)
	{
		//FVector2D	S

		UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(m_ItemDescWidget->Slot);

		if (PanelSlot)
		{
			FVector2D	WidgetPos = InMouseEvent.GetScreenSpacePosition();

			//USlateBlueprintLibrary::ScreenToWidgetLocal(this, InGeometry,
			//	InMouseEvent.GetScreenSpacePosition(), WidgetPos);

			// 마우스의 Screen좌표를 위젯의 Local 좌표로 변경한다.
			WidgetPos = USlateBlueprintLibrary::AbsoluteToLocal(InGeometry,
				WidgetPos);

			WidgetPos.X += 1.f;
			WidgetPos.Y += 1.f;

			PanelSlot->SetPosition(WidgetPos);

			//PrintViewport(1.f, FColor::Red, FString::Printf(TEXT("X : %.5f Y : %.5f"), WidgetPos.X, WidgetPos.Y));
		}
	}

	return FReply::Handled();
}


void UInventoryTile::ItemClick(UObject* Data)
{
	UInventoryItemDataTile* Item = Cast<UInventoryItemDataTile>(Data);

	if (Item)
	{
		m_InventoryTile->RemoveItem(Data);


		if (m_SlotArray.Num() > 20)
		{
			m_InventorySlot->RemoveItem(m_SlotArray[Item->GetIndex()]);
			m_SlotArray.RemoveAt(Item->GetIndex());
			
		}
	}
}



void UInventoryTile::ItemScroll(UObject* Data,UUserWidget* widget)
{
	
}



void UInventoryTile::ItemHovered(UObject* Data,bool Hovered)
{
	m_MouseHovered = Hovered;
	if(Hovered)
	{
		m_ItemDescWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		UInventoryItemDataTile* Item = Cast<UInventoryItemDataTile>(Data);
		float MouseX=0.f,MouseY=0.f;
		GetWorld()->GetFirstPlayerController()->GetMousePosition(MouseX,MouseY);
		if (Item)
		{
			m_ItemDescWidget->SetNameText(Item->GetNameText());
			m_ItemDescWidget->SetIconImage(Item->GetIconTexture());
			//PrintViewport(1.f,FColor::Red,Item->GetNameText());
		}

	}
	else
	{
		m_ItemDescWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}


void UInventoryTile::AddItem(const FUIItemTableInfo* ItemInfo)
{
	UInventoryItemDataTile* Data = NewObject<UInventoryItemDataTile>(this,
		UInventoryItemDataTile::StaticClass());

	Data->SetIcon(ItemInfo->IconTexture);
	Data->SetNameText(ItemInfo->Name);
	Data->SetIndex(m_InventoryTile->GetNumItems());

	m_InventoryTile->AddItem(Data);
}