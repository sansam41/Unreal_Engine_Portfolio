// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"


void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_InventoryButton = Cast<UButton>(GetWidgetFromName(TEXT("InventoryButton")));
	m_CharacterStateButton = Cast<UButton>(GetWidgetFromName(TEXT("CharacterStateButton")));
	m_SkillButton = Cast<UButton>(GetWidgetFromName(TEXT("SkillButton")));
	m_OptionButton = Cast<UButton>(GetWidgetFromName(TEXT("OptionButton")));

	m_InventoryButton->OnClicked.AddDynamic(this,&UMainMenuWidget::OnInventory);
	m_CharacterStateButton->OnClicked.AddDynamic(this,&UMainMenuWidget::OnInventoryTile);
	m_SkillButton->OnClicked.AddDynamic(this,&UMainMenuWidget::OnAuctionWidget);
	m_OptionButton->OnClicked.AddDynamic(this,&UMainMenuWidget::OnQuestWidget);
}
void UMainMenuWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UMainMenuWidget::OnInventory()
{
	if(m_InventoryList->GetVisibility()==ESlateVisibility::Collapsed)
	{
		m_InventoryList->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		m_InventoryList->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UMainMenuWidget::OnInventoryTile()
{
	if(m_InventoryTile->GetVisibility()==ESlateVisibility::Collapsed)
	{
		m_InventoryTile->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		m_InventoryTile->SetVisibility(ESlateVisibility::Collapsed);
	}
}
void UMainMenuWidget::OnAuctionWidget()
{
	if(m_AuctionWidget->GetVisibility()==ESlateVisibility::Collapsed)
	{
		m_AuctionWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		m_AuctionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UMainMenuWidget::OnQuestWidget()
{
	if(m_QuestWidget->GetVisibility()==ESlateVisibility::Collapsed)
	{
		m_QuestWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		m_QuestWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}