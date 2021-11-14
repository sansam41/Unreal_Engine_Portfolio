// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Chaos/ChaosDebugDraw.h"
#include "UObject/NoExportTypes.h"
#include "QuestListItemData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class UEKR2_API UQuestListItemData : public UObject
{
	GENERATED_BODY()
public:
	UQuestListItemData();
private:
	FString m_Name;
	int32 m_Index;
	class UQuestListItemWidget* m_OwnerWidget;
public:
	class UQuestListItemWidget* GetOwnerWidget()
	{
		return m_OwnerWidget;
	}
	
	void SetOwnerWidger(class UQuestListItemWidget* Widget)
	{
		m_OwnerWidget = Widget;
	}
	void SetQuestName(const FString& Name)
	{
		m_Name = Name;
	}

	const FString& GetQuestName()
	{
		return m_Name;
	}

	
	void SetIndex(int32 Index)
	{
		m_Index = Index;
	}
	
	int32 GetIndex()
	{
		return m_Index;
	}
	
	
};
