// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestWidget.h"

#include "MainHUD.h"
#include "QuestListItemData.h"
#include "QuestListItemWidget.h"
#include "../UEKR2GameInstance.h"
#include "UEKR2/RPG/RPGGameModeBase.h"
#include "UEKR2/RPG/Player/RPG_PlayerCharacter.h"


void UQuestWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_QuestList = Cast<UListView>(GetWidgetFromName(TEXT("QuestList")));
	m_QuestDesc = Cast<UQuestDescWidget>(GetWidgetFromName(TEXT("UI_QuestDesc")));

	m_QuestList->OnItemClicked().AddUObject(this, &UQuestWidget::QuestClick);
	m_QuestList->OnItemSelectionChanged().AddUObject(this, &UQuestWidget::QuestSelect);
	m_QuestList->OnItemIsHoveredChanged().AddUObject(this, &UQuestWidget::QuestMouseOn);

	m_CurrentRenderQuest = nullptr;

	

	m_PrevSelect = nullptr;
}

void UQuestWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UQuestWidget::QuestClick(UObject* Data)
{
	UQuestListItemData* Info = Cast<UQuestListItemData>(Data);
	
	
	if (Info)
	{
		if (m_CurrentRenderQuest == &m_QuestArray[Info->GetIndex()])
			return;
		
		m_CurrentRenderQuest = &m_QuestArray[Info->GetIndex()];

		FString	QuestName = m_QuestArray[Info->GetIndex()].Name;

		if (m_CurrentRenderQuest->Complete)
			QuestName = m_QuestArray[Info->GetIndex()].Name + TEXT("(Completed)");

		m_QuestDesc->SetQuestName(QuestName);
		m_QuestDesc->SetQuestDesc(m_QuestArray[Info->GetIndex()].QuestDesc);
		PrintViewport(1.f,FColor::Red,m_QuestArray[Info->GetIndex()].QuestDesc);
		m_QuestDesc->ClearList();

		int32	Index = 0;

		for (auto& DataInfo : m_QuestArray[Info->GetIndex()].CompleteArray)
		{
			m_QuestDesc->AddList(DataInfo, Index);
			++Index;
		}
	}
}

void UQuestWidget::QuestSelect(UObject* Data)
{
	UQuestListItemData* Item = Cast<UQuestListItemData>(Data);

	if(m_PrevSelect)
		m_PrevSelect->GetOwnerWidget()->Select(false);

	Item->GetOwnerWidget()->Select(true);
	
	m_PrevSelect = Item;
}

void UQuestWidget::QuestMouseOn(UObject* Data, bool IsHovered)
{
	UQuestListItemData* Item = Cast<UQuestListItemData>(Data);

	Item->GetOwnerWidget()->MouseOn(IsHovered);
}


void UQuestWidget::QuestAdd(const FString& QuestName)
{
	
	UUEKR2GameInstance* GameInst = Cast<UUEKR2GameInstance>(GetWorld()->GetGameInstance());

	if (GameInst)
	{
		const TMap<FString, FQuestData>& QuestData = GameInst->GetQuestData();

		int32	Index = 0;

		for (auto& Data : QuestData)
		{
			if(Data.Key==QuestName)
			{
				const FQuestTableInfo* Info = GameInst->FindQuestInfo(Data.Key);

				PrintViewport(1.f,FColor::Red,Data.Key);
				if (Info)
				{
					m_QuestArray.Add(Data.Value);
			
					int32	QuestIndex = m_QuestArray.Num() - 1;
					m_QuestArray[QuestIndex].accept=true;
					for (auto& QuestInfo : Info->InfoArray)
					{
						m_QuestListArray[(uint8)QuestInfo.Type].Add(&m_QuestArray[QuestIndex]);
					}

					UQuestListItemData* QuestItemData = NewObject<UQuestListItemData>(this,
						UQuestListItemData::StaticClass());

					QuestItemData->SetIndex(Index);
					QuestItemData->SetQuestName(Info->Name);
				
					m_QuestList->AddItem(QuestItemData);
				}
			}
			++Index;
		}
	}
}

void UQuestWidget::QuestCheck(EQuestType Type, const FString& Name)
{
	for (auto& Info : m_QuestListArray[(uint8)Type])
	{
		if (Info->Complete)
			continue; 
		int32	CompleteCount = 0;

		for (auto& QuestData : Info->CompleteArray)
		{
			
			if (QuestData.Complete)
			{
				++CompleteCount;
				continue;
			}

			if (QuestData.Type == Type && QuestData.DestName == Name)
			{
				++QuestData.Count;

				if (QuestData.Count == QuestData.MaxCount)
				{
					QuestData.Complete = true;
					++CompleteCount;
				}
				
				// 현재 퀘스트창에 보여지고 있는 퀘스트가 변경이 일어났을 경우
				// 갱신한다.
				if (m_CurrentRenderQuest == Info)
				{
					m_QuestDesc->SetQuestName(m_CurrentRenderQuest->Name);
					m_QuestDesc->SetQuestDesc(m_CurrentRenderQuest->QuestDesc);

					m_QuestDesc->ClearList();

					int32	CompleteIndex = 0;

					for (auto& DataInfo : m_CurrentRenderQuest->CompleteArray)
					{
						m_QuestDesc->AddList(DataInfo, CompleteIndex);
						++CompleteIndex;
					}
				}

				break;
			}
		}

		if (CompleteCount == Info->CompleteArray.Num())
		{
			Info->Complete = true;
			
		}
	}
}

bool UQuestWidget::QuestClearCheck(int32 Qnum)
{
	if(m_QuestArray.Num()<=Qnum)
		return false;
	return m_QuestArray[Qnum].Complete;
}


void UQuestWidget::QuestReward(int32 Qnum)
{
	
	// 퀘스트 완료시 보상 처리
	for(auto& Rewards: m_QuestArray[Qnum].RewardArray)
	{
		switch(Rewards.Type)
		{
		case EQuestRewardType::Gold:
			{
				int32 Gold = FCString::Atoi(*Rewards.Reward);
							
				ARPG_PlayerCharacter* Player = GetWorld()->GetFirstPlayerController()->GetPawn<ARPG_PlayerCharacter>();
							
				if(Player)
				{
					Player->AddGold(Gold);
				}
							
			}
			break;
					
		case EQuestRewardType::Exp:
			{
				int32 Exp = FCString::Atoi(*Rewards.Reward);
					
				ARPG_PlayerCharacter* Player = GetWorld()->GetFirstPlayerController()->GetPawn<ARPG_PlayerCharacter>();
					
				if(Player)
				{
					Player->AddExp(Exp);
				}
			}
			break;
					
		case EQuestRewardType::Item:
			{
				UUEKR2GameInstance* GameInst = GetWorld()->GetGameInstance<UUEKR2GameInstance>();
				if(GameInst)
				{
					const FUIItemTableInfo* ItemInfo = GameInst->FindUIItemInfo(Rewards.Reward);
					if(ItemInfo)
					{
						ARPGGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ARPGGameModeBase>();
						if(GameMode){
							UMainHUD* MainHud = GameMode->GetMainHUD();

							if(MainHud)
							{
								MainHud->GetMainInventoryList()->AddItem(ItemInfo);
							}
						}
					}
				}
			}
			break;
		}
	}
}
