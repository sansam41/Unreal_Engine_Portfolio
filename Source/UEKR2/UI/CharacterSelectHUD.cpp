// Fill out your copyright notice in the Description page of Project Settings.
#include "CharacterSelectHUD.h"
#include "CharacterHUD.h"
#include "CharacterSelectState.h"
#include "CharacterNameInputWidget.h"
#include "UEKR2/UEKR2GameInstance.h"


void UCharacterSelectHUD::NativeConstruct()
{
	Super::NativeConstruct();
	m_StartButton= Cast<UButton>(GetWidgetFromName(TEXT("StartButton")));
	m_QuitButton= Cast<UButton>(GetWidgetFromName(TEXT("BackButton")));
	m_KnightState= Cast<UCharacterSelectState>(GetWidgetFromName(TEXT("UI_SelectState_Knight")));
	m_ArcherState= Cast<UCharacterSelectState>(GetWidgetFromName(TEXT("UI_SelectState_Archer")));
	m_NameInput= Cast<UCharacterNameInputWidget>(GetWidgetFromName(TEXT("UI_CharacterNameInput")));

	
	m_StartButton->OnClicked.AddDynamic(this,&UCharacterSelectHUD::StartButton);
	m_QuitButton->OnClicked.AddDynamic(this,&UCharacterSelectHUD::BackButton);

	//캐릭터 이미지 재질 로딩
	UMaterialInterface* KnightMaterial = LoadObject<UMaterialInterface>(nullptr,
		TEXT("MaterialInstanceConstant'/Game/UI/MTURenderTargetDepthClear_Inst.MTURenderTargetDepthClear_Inst'"));

	m_KnightState->SetImageMaterial(KnightMaterial);

	
	UMaterialInterface* ArcherMaterial = LoadObject<UMaterialInterface>(nullptr,
		TEXT("MaterialInstanceConstant'/Game/UI/MTURenderTargetDepthClear_Archer.MTURenderTargetDepthClear_Archer'"));

	m_ArcherState->SetImageMaterial(ArcherMaterial);
}
void UCharacterSelectHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}


void UCharacterSelectHUD::StartButton()
{
	FString InputName=m_NameInput->GetInputText();
	UUEKR2GameInstance* GameInst = Cast<UUEKR2GameInstance>(GetWorld()->GetGameInstance());

	if (GameInst)
	{
		GameInst->SetPlayerName(InputName);
	}
	UGameplayStatics::OpenLevel(GetWorld(),TEXT("RPGMain"));
}

void UCharacterSelectHUD::BackButton()
{
	UGameplayStatics::OpenLevel(GetWorld(),TEXT("Start"));
}

void UCharacterSelectHUD::SetKnightStateVisibility(ESlateVisibility Visible)
{
	m_KnightState->SetVisibility(Visible);
}
void UCharacterSelectHUD::SetArcherStateVisibility(ESlateVisibility Visible)
{
	m_ArcherState->SetVisibility(Visible);
}

void UCharacterSelectHUD::SetInputNameVisibility(ESlateVisibility Visible)
{
	m_NameInput->SetVisibility(Visible);
}

void UCharacterSelectHUD::SetKnightInfo(const FPlayerInfo& Info)
{
	m_KnightState->SetNameText(Info.Name);
	m_KnightState->SetJobText(Info.Job);
	m_KnightState->SetAttackText(Info.Attack);
	m_KnightState->SetArmorText(Info.Armor);
	m_KnightState->SetHPText(Info.HP,Info.HPMax);
	m_KnightState->SetMPText(Info.MP,Info.MPMax);
}
void UCharacterSelectHUD::SetArcherInfo(const FPlayerInfo& Info)
{
	m_ArcherState->SetNameText(Info.Name);
	m_ArcherState->SetJobText(Info.Job);
	m_ArcherState->SetAttackText(Info.Attack);
	m_ArcherState->SetArmorText(Info.Armor);
	m_ArcherState->SetHPText(Info.HP,Info.HPMax);
	m_ArcherState->SetMPText(Info.MP,Info.MPMax);
}

