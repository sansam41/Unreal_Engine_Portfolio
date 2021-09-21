// Fill out your copyright notice in the Description page of Project Settings.


#include "UEKR2GameInstance.h"


UUEKR2GameInstance::UUEKR2GameInstance() 
{
	static ConstructorHelpers::FObjectFinder<UDataTable> MonsterInfoTableAsset(TEXT("DataTable'/Game/Monster/DTMonsterInfo.DTMonsterInfo'"));
	if (MonsterInfoTableAsset.Succeeded())
		m_MonsterInfoTable = MonsterInfoTableAsset.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable> PlayerInfoTableAsset(TEXT("DataTable'/Game/Player/DTPlayerInfo.DTPlayerInfo'"));
	if (PlayerInfoTableAsset.Succeeded())
		m_PlayerInfoTable = PlayerInfoTableAsset.Object;
	
	static ConstructorHelpers::FObjectFinder<UDataTable> UIItemInfoTableAsset(TEXT("DataTable'/Game/UI/DTUIItemInfo.DTUIItemInfo'"));
	if (PlayerInfoTableAsset.Succeeded())
		m_UIItemInfoTable = UIItemInfoTableAsset.Object;
}
void UUEKR2GameInstance::Init() 
{
	Super::Init();
}

const FMonsterTableInfo* UUEKR2GameInstance::FindMonsterInfo(const FString& Name) 
{
	return m_MonsterInfoTable->FindRow<FMonsterTableInfo>(*Name,"");
}
const FPlayerTableInfo* UUEKR2GameInstance::FindPlayerInfo(const FString& Name) 
{
	return m_PlayerInfoTable->FindRow<FPlayerTableInfo>(*Name,"");
}

const FUIItemTableInfo* UUEKR2GameInstance::FindUIItemInfo(const FString& Name) 
{
	return m_UIItemInfoTable->FindRow<FUIItemTableInfo>(*Name,"");
}
