// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "UObject/NoExportTypes.h"
#include "InventoryItemDataTile.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API UInventoryItemDataTile : public UObject
{
	GENERATED_BODY()
public:
	UInventoryItemDataTile();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString	m_IconPath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString	m_NameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	m_Index;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTexture2D* m_IconTexture;

public:

	UTexture2D* GetIconTexture()
	{
		return m_IconTexture;
	}
	
	int32 GetIndex()
	{
		return m_Index;
	}

	FString GetNameText()
	{
		return m_NameText;
	}
	

	public:
	void SetIcon(UTexture2D* IconTex)
	{
		m_IconTexture=IconTex;
	}

	void SetIndex(int32 Index)
	{
		m_Index = Index;
	}	
	void SetNameText(const FString& Name)
	{
		m_NameText = Name;
	}	
};
