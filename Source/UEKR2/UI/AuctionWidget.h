// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AuctionList.h"
#include "InventoryList.h"
#include "../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/TreeView.h"
#include "AuctionWidget.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API UAuctionWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	UTreeView*  m_Menu;
	
	bool	m_MouseHovered;

	class UAuctionItemData* m_SelectionItem;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	UAuctionList*  m_AuctionList;
	
public:

	protected:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

public:
	UFUNCTION(BlueprintCallable)
	void ItemClick(UObject* Data);

	UFUNCTION()
	void ItemHovered(UObject* Data,bool Hovered);
	
	UFUNCTION()
	void GetItemChildren(UObject* Data,TArray<UObject*>& ItemArray);
};
