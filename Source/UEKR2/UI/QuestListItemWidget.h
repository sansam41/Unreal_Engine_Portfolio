// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "QuestListItemData.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "QuestListItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API UQuestListItemWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	UTextBlock*  m_NameText;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	UImage*  m_Selection;

	bool m_Select;

	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UFUNCTION(BlueprintCallable)
	void SetData(UObject* Data);

	void MouseOn(bool Enable);
	void Select(bool Enable);
};
