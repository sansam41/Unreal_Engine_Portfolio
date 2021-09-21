// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AuctionWidget.h"
#include "../GameInfo.h"
#include "MainMenuWidget.h"
#include "CharacterHUD.h"
#include "InventoryList.h"

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

	class UMaterialParameterCollection* m_LandScapeCollection;
	class UMaterialParameterCollectionInstance* m_LandScapeCollectionInst;


public:
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
	void ShowUI(bool Show);
	

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UFUNCTION()
	void LandScapeSliderValue(float Value);
};
