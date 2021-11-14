// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AuctionWidget.h"
#include "../GameInfo.h"
#include "MainMenuWidget.h"
#include "CharacterHUD.h"
#include "InventoryList.h"
#include "ChatWidget.h"
#include "QuestWidget.h"
#include "MinimapWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Slider.h"
#include "MainHUD.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API UMainHUD : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	UCharacterHUD*  m_CharacterHUD;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	UMainMenuWidget*  m_MainMenu;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	UInventoryList*  m_InventoryList;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	UInventoryTile*  m_InventoryTile;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	UAuctionWidget*  m_Auction;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	USlider*  m_LandScapeSlider;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	UChatWidget*  m_ChatWidget;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	UQuestWidget*  m_QuestWidget;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	UMinimapWidget*  m_Minimap;

	class UMaterialParameterCollection* m_LandScapeCollection;
	class UMaterialParameterCollectionInstance* m_LandScapeCollectionInst;


public:
	UChatWidget* GetChatWidget()
	{
		return m_ChatWidget;
	}
	
	UCharacterHUD* GetCharacterHUD()
	{
		return m_CharacterHUD;
	}
	UMainMenuWidget* GetMainMenuHUD()
	{
		return m_MainMenu;
	}
	UInventoryList* GetMainInventoryList()
	{
		return m_InventoryList;
	}
	UInventoryTile* GetInventoryTile()
	{
		return m_InventoryTile;
	}
	
	UQuestWidget* GetQuestWidget()
	{
		return m_QuestWidget;
	}
	
	UMinimapWidget* GetMinimapWidget()
	{
		return m_Minimap;
	}
	void ShowUI(bool Show);
	

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UFUNCTION()
	void LandScapeSliderValue(float Value);
};
