// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/ListView.h"
#include "InventoryItemList.h"
#include "InventoryItemDataList.h"
#include "Blueprint/UserWidget.h"
#include "InventoryList.generated.h"

DECLARE_DELEGATE(FInventoryInit)

/**
 * 
 */
UCLASS()
class UEKR2_API UInventoryList : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	UListView*  m_InventoryList;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	UTextBlock*  m_GoldText;

	FInventoryInit m_InventoryInitDelegate;

public:

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UFUNCTION()
	void ItemClick(UObject* Data);

public:
	void AddItem(const FUIItemTableInfo* ItemInfo);
	bool FindItem(const FString& ItemName);
	void SetGold(int32 Gold);

public:
	template <typename T>
	void SetInventoryInitDelegate(T* Obj, void(T::* Func)())
	{
		m_InventoryInitDelegate.BindUObject(Obj,Func);
	}
};
