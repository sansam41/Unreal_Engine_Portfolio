// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUD.h"

#include "NpcDialogue.h"

void UMainHUD::NativeConstruct()
 {
	Super::NativeConstruct();

 	m_CharacterHUD = Cast<UCharacterHUD>(GetWidgetFromName(TEXT("UI_CharacterHUD")));
 	m_MainMenu = Cast<UMainMenuWidget>(GetWidgetFromName(TEXT("UI_MainMenu")));
 	m_InventoryList = Cast<UInventoryList>(GetWidgetFromName(TEXT("UI_InventoryList")));
 	m_InventoryTile = Cast<UInventoryTile>(GetWidgetFromName(TEXT("UI_InventoryTile")));
 	m_Auction = Cast<UAuctionWidget>(GetWidgetFromName(TEXT("UI_AuctionWidget")));
 	m_LandScapeSlider = Cast<USlider>(GetWidgetFromName(TEXT("LandScapeTiling")));
 	m_ChatWidget = Cast<UChatWidget>(GetWidgetFromName(TEXT("UI_Chat")));
 	m_QuestWidget = Cast<UQuestWidget>(GetWidgetFromName(TEXT("UI_Quest")));
 	m_Minimap = Cast<UMinimapWidget>(GetWidgetFromName(TEXT("UI_Minimap")));
 	m_NpcTalk = Cast<UUserWidget>(GetWidgetFromName(TEXT("UI_TalkNpc")));
 	m_NpcDialogue = Cast<UNpcDialogue>(GetWidgetFromName(TEXT("UI_QuestNpc")));
 	

	m_LandScapeSlider->OnValueChanged.AddDynamic(this,&UMainHUD::LandScapeSliderValue);

 	// 에셋을 컬렉션으로 불러오고 컬렉션을 통해 인스턴스를 만듦
 	// 실질적인 관리는 인스턴스를 통해 만듦
 	m_LandScapeCollection = LoadObject<UMaterialParameterCollection>(GetWorld(),TEXT("MaterialParameterCollection'/Game/LandScape/MCMainLandScapeData.MCMainLandScapeData'"));
	m_LandScapeCollectionInst = GetWorld()->GetParameterCollectionInstance(m_LandScapeCollection);
 	
 	m_MainMenu->SetInventoryList(m_InventoryList);
 	m_MainMenu->SetInventoryTile(m_InventoryTile);
 	m_MainMenu->SetAuctionWidget(m_Auction);
 	m_MainMenu->SetQuestWidget(m_QuestWidget);


 	m_MainMenu->SetVisibility(ESlateVisibility::Collapsed);
 	
 	//m_MainMenu->SetInventoryButtonClickCallback<UMainHUD>(this,&UMainHUD::InventoryButtonClick);
 }
 void UMainHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
 {
	Super::NativeTick(MyGeometry, InDeltaTime);
 }

 void UMainHUD::LandScapeSliderValue(float Value)
 {
	 m_LandScapeCollectionInst->SetScalarParameterValue(TEXT("Tiling"),Value);
 }


 void UMainHUD::ShowUI(bool Show)
 {
 	if(Show==true)
 		m_MainMenu->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
 	else
 		m_MainMenu->SetVisibility(ESlateVisibility::Collapsed);

 }
 void UMainHUD::ShowNpcDialogue(bool Show)
 {
 	if(Show==true)
 		m_NpcDialogue->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
 	else
 		m_NpcDialogue->SetVisibility(ESlateVisibility::Collapsed);

 }

void UMainHUD::ShowNpcTalkKey(bool Show)
 {
 	if(Show==true)
 		m_NpcTalk->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
 	else
 		m_NpcTalk->SetVisibility(ESlateVisibility::Collapsed);
 }

