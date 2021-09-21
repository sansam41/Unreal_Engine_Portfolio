// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "UObject/NoExportTypes.h"
#include "AuctionItemData.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API UAuctionItemData : public UObject
{
	GENERATED_BODY()

public:
	UAuctionItemData();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString	m_NameText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<UObject*>	m_ChildArray;

	UAuctionItemData* m_Parent;

	int32 m_TreeLevel;
	int32 m_Index;

	class UAuctionItem* m_LinkItem;

public:
	TArray<UObject*>& GetChildArray()
	{
		return m_ChildArray;
	}

public:
	int32 GetTreeLevel() const
	{
		return m_TreeLevel;
	}
	FString GetNameText()
	{
		return m_NameText;
	}
public:
	void SetNameText(const FString& Name)
	{
		m_NameText = Name;
	}
	void SetParent(UAuctionItemData* Parent)
	{
		m_Parent=Parent;
	}

	void SetLinkItem(class UAuctionItem* Item)
	{
		m_LinkItem=Item;
	}

public:
	void Selection();
	void UnSelection();
	
	

	UFUNCTION(BlueprintCallable)
	void CreateChildren(const FString& Name);
};