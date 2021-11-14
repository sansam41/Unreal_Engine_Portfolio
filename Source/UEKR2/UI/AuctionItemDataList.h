// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "UObject/NoExportTypes.h"
#include "AuctionItemDataList.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API UAuctionItemDataList : public UObject
{
	GENERATED_BODY()
public:

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	FString m_NameText;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	UTexture2D* m_Icon;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	FString m_ItemType;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	FString m_ItemSubType;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	int32 m_Index;

	
public:
	FString GetNameText()
	{
		return m_NameText;
	}

	UTexture2D* GetIcon()
	{
		return m_Icon;
	}

	FString GetType()
	{
		return m_ItemType;
	}
	FString GetSubType()
	{
		return m_ItemSubType;
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
	
	void SetIcon(UTexture2D* Icon)
	{
		m_Icon = Icon;
	}

	void SetType(const FString& Type,const FString& subType)
	{
		m_ItemType=Type;
		m_ItemSubType=subType;
	}

	void SetIndex(int32 Index)
	{
		m_Index=Index;
	}
	

	
	
};
