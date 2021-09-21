// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "AuctionList.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API UAuctionList : public UUserWidget
{
	GENERATED_BODY()
	protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	UListView*  m_AuctionList;

	public:
	TArray<class UAuctionItemDataList*> m_ItemArray;

	protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	void SetAuctionList(FString Name);
	
	public:
	UFUNCTION()
	void ItemClick(UObject* Data);
};
