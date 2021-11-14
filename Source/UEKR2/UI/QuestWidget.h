// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "QuestDescWidget.h"
#include "QuestWidget.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API UQuestWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	UListView*  m_QuestList;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	UQuestDescWidget*  m_QuestDesc;

	FQuestData* m_CurrentRenderQuest;
	int32	m_CurrentRenderIndex;

	TArray<FQuestData> m_QuestArray;

	TArray<FQuestData*> m_QuestListArray[(uint8)EQuestType::Max];

	class UQuestListItemData* m_PrevSelect;
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UFUNCTION()
	void QuestClick(UObject* Data);
	UFUNCTION()
	void QuestSelect(UObject* Data);
	UFUNCTION()
	void QuestMouseOn(UObject* Data,bool IsHovered);

public:
	void QuestCheck(EQuestType Type, const FString& Name);
};
