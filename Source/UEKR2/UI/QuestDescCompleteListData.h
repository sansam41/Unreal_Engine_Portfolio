// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "UObject/NoExportTypes.h"
#include "QuestDescCompleteListData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class UEKR2_API UQuestDescCompleteListData : public UObject
{
	GENERATED_BODY()
	
public:
	UQuestDescCompleteListData();

protected:
	FString m_TypeText;
	FString m_DestText;
	FString m_CountText;
	int32	m_Count;
	int32	m_CountMax;
	int32	m_Index;
	class UQuestDescCompleteListWidget* m_OwnerWidget;

	
public:
	int32 GetIndex()	const
	{
		return m_Index;
	}

	int32 GetCount()	const
	{
		return m_Count;
	}

	int32 GetCountMax()	const
	{
		return m_CountMax;
	}

	const FString& GetTypeText()	const
	{
		return m_TypeText;
	}

	const FString& GetDestText()	const
	{
		return m_DestText;
	}

	const FString& GetCountText()	const
	{
		return m_CountText;
	}

	void SetIndex(int32 Index)
	{
		m_Index = Index;
	}

	void SetTypeText(const FString& Text)
	{
		m_TypeText = Text;
	}

	void SetDestText(const FString& Text)
	{
		m_DestText = Text;
	}

	void SetCountText(int32 Count, int32 CountMax)
	{
		m_Count = Count;
		m_CountMax = CountMax;
		if(m_Count==m_CountMax)
			m_CountText = TEXT("Complete!");
		else
			m_CountText = FString::Printf(TEXT("%d / %d"), Count, CountMax);
	}

	void SetOwnerWidget(class UQuestDescCompleteListWidget* Widget)
	{
		m_OwnerWidget = Widget;
	}
};

