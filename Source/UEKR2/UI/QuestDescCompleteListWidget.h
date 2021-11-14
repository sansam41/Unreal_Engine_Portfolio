// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "QuestDescCompleteListWidget.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API UQuestDescCompleteListWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	UTextBlock*  m_DestText;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	UTextBlock*  m_TypeText;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	UTextBlock*  m_CountText;

	int32 m_Index;

public:
	int32 GetIndex()	const
	{
		return m_Index;
	}

	void SetIndex(int32 Index)
	{
		m_Index = Index;
	}

	void SetTypeText(const FString& Text)
	{
		m_TypeText->SetText(FText::FromString(Text));
	}

	void SetDescText(const FString& Text)
	{
		m_DestText->SetText(FText::FromString(Text));
	}

	void SetCountText(const FString& Text)
	{
		m_CountText->SetText(FText::FromString(Text));
	}

protected:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject);
	virtual void NativeOnItemSelectionChanged(bool bIsSelected);
};

