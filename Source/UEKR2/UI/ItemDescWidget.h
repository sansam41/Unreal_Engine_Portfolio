// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ItemDescWidget.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API UItemDescWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	UImage*  m_IconImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTextBlock* m_NameText;


public:

protected:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
public:
	void SetNameText(const FString& Name)
	{
		m_NameText->SetText(FText::FromString(Name));
	}
	void SetIconImage(UTexture2D* Tex)
	{
		m_IconImage->SetBrushFromTexture(Tex);
	}
};
