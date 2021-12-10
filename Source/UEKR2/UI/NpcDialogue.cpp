// Fill out your copyright notice in the Description page of Project Settings.


#include "NpcDialogue.h"

#include "UEKR2/RPG/RPGGameModeBase.h"
#include "UEKR2/RPG/Npc/CastleNpc.h"
#include "UEKR2/RPG/Npc/NpcBase.h"
#include "UEKR2/RPG/Npc/QuestNpc.h"

void UNpcDialogue::NativeConstruct()
{
	Super::NativeConstruct();
	m_Npc = nullptr;
	
	m_NameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Npc_Name")));
	m_NpcDialogue = Cast<UMultiLineEditableTextBox>(GetWidgetFromName(TEXT("NPC_Dialogue")));

	
	m_YesButton = Cast<UButton>(GetWidgetFromName(TEXT("YesButton")));
	m_NoButton = Cast<UButton>(GetWidgetFromName(TEXT("NoButton")));


	
	m_YesButton->OnClicked.AddDynamic(this,&UNpcDialogue::YesButtonClicked);
	m_NoButton->OnClicked.AddDynamic(this,&UNpcDialogue::NoButtonClicked);
	if(m_NpcDialogueDelegate.IsBound())
	{
		m_NpcDialogueDelegate.Execute();
	}

	
	SetVisibility(ESlateVisibility::Collapsed);
}

void UNpcDialogue::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}


void UNpcDialogue::YesButtonClicked()
{
	
	PrintViewport(1.f,FColor::Red,m_Npc->m_NpcInfo.Name+TEXT(" In"));
	ARPGGameModeBase* GameMode = Cast<ARPGGameModeBase>(GetWorld()->GetAuthGameMode());
	if(IsValid(GameMode))
	{
		UMainHUD* MainHud = GameMode->GetMainHUD();

		if(IsValid(MainHud)&&m_Npc->m_NpcInfo.Type==1)
		{
			if(MainHud->GetQuestWidget()->QuestClearCheck(m_Npc->m_QuestProgress))
			{
				MainHud->GetQuestWidget()->QuestReward(m_Npc->m_QuestProgress);
				Cast<AQuestNpc>(m_Npc)->NextQuest();
				m_Npc->SetOrdered(false);
				
			}
			else if(m_Npc->GetOrdered()==false)
			{
				MainHud->GetQuestWidget()->QuestAdd("Quest"+FString::FromInt(m_Npc->m_QuestProgress));
				m_Npc->SetOrdered(true);
			}
			SetVisibility(ESlateVisibility::Collapsed);
		}
		else if(IsValid(MainHud)&&m_Npc->m_NpcInfo.Type==2)
		{
			
			Cast<ACastleNpc>(m_Npc)->NextDialogue();
			if(Cast<ACastleNpc>(m_Npc)->m_checked == true)
			{
				if(Cast<ACastleNpc>(m_Npc)->m_key == true)
				{
					Cast<ACastleNpc>(m_Npc)->MovePlayer();
				}
				SetVisibility(ESlateVisibility::Collapsed);
				Cast<ACastleNpc>(m_Npc)->m_checked = false;
				Cast<ACastleNpc>(m_Npc)->m_key = false;
			}
			else if(m_Npc->m_DialogueProgress<m_Npc->m_NpcInfo.Dialogue.Num())
			{
				SetNpcDialogue(m_Npc->m_NpcInfo.Dialogue[m_Npc->m_DialogueProgress]);
			}
			else
			{
				if(MainHud->GetMainInventoryList()->FindItem(TEXT("열쇠")))
				{
					SetNpcDialogue(m_Npc->m_NpcInfo.Dialogue2[1]);
					Cast<ACastleNpc>(m_Npc)->m_checked = true;
					Cast<ACastleNpc>(m_Npc)->m_key = true;
				}
				else
				{
					SetNpcDialogue(m_Npc->m_NpcInfo.Dialogue2[0]);
					Cast<ACastleNpc>(m_Npc)->m_checked = true;
					Cast<ACastleNpc>(m_Npc)->m_key = false;
				}
			}
		}
	}
}

void UNpcDialogue::NoButtonClicked()
{
	SetVisibility(ESlateVisibility::Collapsed);
	PrintViewport(1.f,FColor::Red,m_Npc->m_NpcInfo.Name+TEXT(" Out"));
	if(m_Npc->m_NpcInfo.Type==2)
	{
		m_Npc->m_DialogueProgress=0;
		Cast<ACastleNpc>(m_Npc)->m_checked = false;
		Cast<ACastleNpc>(m_Npc)->m_key = false;
	}
}