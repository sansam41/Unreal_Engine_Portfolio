// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "StartWidget.generated.h"


UCLASS()
class UEKR2_API UStartWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	UButton*  m_StartButton;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	UButton*  m_QuitButton;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	UWidgetAnimation*  m_StartButtonMouseOn;

	

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	void BindingAnimations();
	
public:
	UFUNCTION()
	void StartButton();
	UFUNCTION()
	void QuitButton();
	UFUNCTION()
	void StartButtonHovered();
	UFUNCTION()
	void QuitButtonHovered();
};
