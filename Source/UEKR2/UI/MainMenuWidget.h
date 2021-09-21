// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AuctionWidget.h"
#include "InventoryList.h"
#include "InventoryTile.h"
#include "../GameInfo.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	UButton*  m_InventoryButton;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	UButton*  m_CharacterStateButton;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	UButton*  m_SkillButton;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	UButton*  m_OptionButton;

	UInventoryList* m_InventoryList;
	UInventoryTile* m_InventoryTile;
	UAuctionWidget* m_AuctionWidget;

public:
	void SetInventoryList(UInventoryList* List)
	{
		m_InventoryList=List;
	}
	void SetInventoryTile(UInventoryTile* Tile)
	{
		m_InventoryTile=Tile;
	}

	void SetAuctionWidget(UAuctionWidget* Auction)
	{
		m_AuctionWidget=Auction;
	}
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UFUNCTION()
	void OnInventory();

	UFUNCTION()
	void OnInventoryTile();
	
	UFUNCTION()
	void OnAuctionWidget();
};
