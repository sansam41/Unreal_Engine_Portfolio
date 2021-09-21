// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "HPBar.generated.h"

/**
 * 
 */

DECLARE_DELEGATE(FNameDelegate);

UCLASS()
class UEKR2_API UHPBar : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	UProgressBar*  m_HPBar;


	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	UTextBlock*  m_NameText;
	
	FNameDelegate m_NameDelegate;

	
public:
	void SetHPPercent(float Percent)
	{
		m_HPBar->SetPercent(Percent);
	}

	void SetName(const FString& Name)
	{
		m_NameText->SetText(FText::FromString(Name));
	}
	


protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	template <typename T>
	void SetDelegate(T* Obj, void(T::* Func)())
	{
		m_NameDelegate.BindUObject(Obj, Func);

		
	}
};
