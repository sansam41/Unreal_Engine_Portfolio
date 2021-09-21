// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "CharacterSelectHUD.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API UCharacterSelectHUD : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	UButton*  m_StartButton;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	UButton*  m_QuitButton;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	class UCharacterSelectState*  m_KnightState;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	class UCharacterSelectState*  m_ArcherState;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	class UCharacterNameInputWidget*  m_NameInput;

	

	

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
public:
	UFUNCTION()
	void StartButton();
	UFUNCTION()
	void BackButton();
public:
	void EnableStartButton(bool Enable)
	{
		m_StartButton->SetIsEnabled(Enable);
	}


	void SetKnightStateVisibility(ESlateVisibility Visible);
	void SetArcherStateVisibility(ESlateVisibility Visible);
	void SetInputNameVisibility(ESlateVisibility Visible);
	void SetKnightInfo(const FPlayerInfo& Info);
	void SetArcherInfo(const FPlayerInfo& Info);
};
