// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "QuestDescCompleteListData.h"
#include "QuestListItemData.h"
#include "Components/TextBlock.h"
#include "Components/ListView.h"
#include "Blueprint/UserWidget.h"
#include "QuestDescWidget.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API UQuestDescWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	UTextBlock*  m_NameText;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	UTextBlock*  m_DescText;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	UListView*  m_CompleteList;
	
public:
	void SetQuestName(const FString& Name)
	{
		m_NameText->SetText(FText::FromString(Name));
	}
	void SetQuestDesc(const FString& Desc)
	{
		m_DescText->SetText(FText::FromString(Desc));
	}

	void ClearList()
	{
		m_CompleteList->ClearListItems();
	}

	void AddList(const FQuestDataInfo& Info,int32 Index)
	{
		UQuestDescCompleteListData* QuestItemData = NewObject<UQuestDescCompleteListData>(this,
			UQuestDescCompleteListData::StaticClass());

		FString	TypeText;
		switch (Info.Type)
		{
		case EQuestType::Collection:
			{
				TypeText = TEXT("Collection");
			}
			break;
		case EQuestType::Hunt:
			{
				TypeText = TEXT("Hunt");
			}
			break;
		case EQuestType::Communication:
			{
				TypeText = TEXT("Communication");
			}
			break;
		}
		

		QuestItemData->SetIndex(Index);
		QuestItemData->SetTypeText(TypeText);
		QuestItemData->SetDestText(Info.DestName);
		QuestItemData->SetCountText(Info.Count, Info.MaxCount);

		m_CompleteList->AddItem(QuestItemData);
	}
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UFUNCTION()
	void QuestCompleteClick(UObject* Data);
};
