// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "UObject/NoExportTypes.h"
#include "InventoryItemDataList.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API UInventoryItemDataList : public UObject
{
	GENERATED_BODY()

public:
	UInventoryItemDataList();

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	FString m_NameText;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	FString m_IconPath;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	int32 m_Index;

	
public:
	FString GetNameText()
	{
		return m_NameText;
	}

	FString GetIconPath()
	{
		return m_IconPath;
	}
	
	int32 GetIndex()
	{
		return m_Index;
	}
	
public:
	void SetNameText(const FString& NameText)
	{
		m_NameText = NameText;
	}
	
	void SetIconPath(const FString& Path)
	{
		m_IconPath = Path;
	}

	void SetIndex(int32 Index)
	{
		m_Index=Index;
	}
	
	
};
