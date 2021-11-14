// Fill out your copyright notice in the Description page of Project Settings.


#include "UEKR2GameInstance.h"
#include "Network/NetworkManager.h"


UUEKR2GameInstance::UUEKR2GameInstance() 
{
	static ConstructorHelpers::FObjectFinder<UDataTable> MonsterInfoTableAsset(TEXT("DataTable'/Game/Monster/DTMonsterInfo.DTMonsterInfo'"));
	if (MonsterInfoTableAsset.Succeeded())
		m_MonsterInfoTable = MonsterInfoTableAsset.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable> PlayerInfoTableAsset(TEXT("DataTable'/Game/Player/DTPlayerInfo.DTPlayerInfo'"));
	if (PlayerInfoTableAsset.Succeeded())
		m_PlayerInfoTable = PlayerInfoTableAsset.Object;
	
	static ConstructorHelpers::FObjectFinder<UDataTable> UIItemInfoTableAsset(TEXT("DataTable'/Game/Item/DTUIItemInfo.DTUIItemInfo'"));
	if (UIItemInfoTableAsset.Succeeded())
		m_UIItemInfoTable = UIItemInfoTableAsset.Object;
	
	static ConstructorHelpers::FObjectFinder<UDataTable> QuestInfoTableAsset(TEXT("DataTable'/Game/Quest/DTQuest.DTQuest'"));
	if (QuestInfoTableAsset.Succeeded())
		m_QuestInfoTable = QuestInfoTableAsset.Object;

	m_SelectJob=EPlayerJob::Knight;
	
}

UUEKR2GameInstance::~UUEKR2GameInstance()
{
	NetworkManager::DestroyInst();
}


void UUEKR2GameInstance::Init() 
{
	Super::Init();
	NetworkManager::GetInst()->Init();

	// 각 퀘스트들이 완료가 되었는지 여부를 가져온다.
	// 임시 퀘스트 하드 코딩
	FQuestData	Data;


	//Quest1
	const FQuestTableInfo* Info = FindQuestInfo(TEXT("Quest1"));
	
	Data.Name = Info->Name;
	Data.QuestDesc = Info->QuestDesc;
	Data.Complete = false;

	for(auto& CompleteData : Info->InfoArray)
	{
		FQuestDataInfo DataInfo;

		DataInfo.Type = CompleteData.Type;
		DataInfo.DestName = CompleteData.DestName;
		DataInfo.MaxCount = CompleteData.Count;
		DataInfo.Count = 0;
		DataInfo.Complete =false;

		Data.CompleteArray.Add(DataInfo);
	}
	

	m_QuestComplete.Add(TEXT("Quest1"), Data);
	
	//Quest2
	Info = FindQuestInfo(TEXT("Quest2"));
	
	Data.Name = Info->Name;
	Data.QuestDesc = Info->QuestDesc;

	Data.CompleteArray.RemoveAll([](FQuestDataInfo v){return true;});

	for(auto& CompleteData : Info->InfoArray)
	{
		FQuestDataInfo DataInfo;

		DataInfo.Type = CompleteData.Type;
		DataInfo.DestName = CompleteData.DestName;
		DataInfo.MaxCount = CompleteData.Count;
		DataInfo.Count = 0;
		DataInfo.Complete =false;

		Data.CompleteArray.Add(DataInfo);
	}
	
	m_QuestComplete.Add(TEXT("Quest2"), Data);

	
	//Quest3
	Info = FindQuestInfo(TEXT("Quest3"));
	
	Data.Name = Info->Name;
	Data.QuestDesc = Info->QuestDesc;
	
	
	Data.CompleteArray.RemoveAll([](FQuestDataInfo v){return true;});

	for(auto& CompleteData : Info->InfoArray)
	{
		FQuestDataInfo DataInfo;

		DataInfo.Type = CompleteData.Type;
		DataInfo.DestName = CompleteData.DestName;
		DataInfo.MaxCount = CompleteData.Count;
		DataInfo.Count = 0;
		DataInfo.Complete =false;
		Data.CompleteArray.Add(DataInfo);
	}
	m_QuestComplete.Add(TEXT("Quest3"), Data);

	//Quest4
	Info = FindQuestInfo(TEXT("Quest4"));
	
	Data.Name = Info->Name;
	Data.QuestDesc = Info->QuestDesc;
	
	
	Data.CompleteArray.RemoveAll([](FQuestDataInfo v){return true;});

	for(auto& CompleteData : Info->InfoArray)
	{
		FQuestDataInfo DataInfo;

		DataInfo.Type = CompleteData.Type;
		DataInfo.DestName = CompleteData.DestName;
		DataInfo.MaxCount = CompleteData.Count;
		DataInfo.Count = 0;
		DataInfo.Complete =false;

		Data.CompleteArray.Add(DataInfo);
	}
	m_QuestComplete.Add(TEXT("Quest4"), Data);

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

const FQuestTableInfo* UUEKR2GameInstance::FindQuestInfo(const FString& Name)
{
	return m_QuestInfoTable->FindRow<FQuestTableInfo>(*Name,"");
}
