// Fill out your copyright notice in the Description page of Project Settings.


#include "AuctionItemData.h"
#include "AuctionItem.h"

UAuctionItemData::UAuctionItemData()
{
	m_TreeLevel=0;
}


void UAuctionItemData::CreateChildren(const FString& Name)
{
	UAuctionItemData* Child=NewObject<UAuctionItemData>(this,
			UAuctionItemData::StaticClass());
		
	Child->m_TreeLevel =m_TreeLevel+1;
	//Child->m_NameText=FString::Printf(TEXT("Child%d~%d"),m_TreeLevel,i);
	Child->m_NameText=Name;
	Child->SetParent(this);
	m_ChildArray.Add(Child);
}

void UAuctionItemData::Selection()
{
	m_LinkItem->Selection();
}
void UAuctionItemData::UnSelection()
{
	m_LinkItem->UnSelection();
}