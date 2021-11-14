// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectPlayerController.h"
#include "SelectPlayer.h"
#include "SelectPlayerAnimInstance.h"
#include "../UI/CharacterSelectHUD.h"
#include "../UEKR2GameInstance.h"
#include "UEKR2/CharacterSelectGameMode.h"

ASelectPlayerController::ASelectPlayerController()
{
	bShowMouseCursor=true;
	m_LButtonClick=false;
	m_SelectJob = EPlayerJob::End;

	m_SelectCharacter = nullptr;
	
}
void ASelectPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	
	Picking();
}
void ASelectPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction(TEXT("CharacterSelect"),
		EInputEvent::IE_Pressed,this,&ASelectPlayerController::MouseClick);
	InputComponent->BindAction(TEXT("CharacterSelect"),
		EInputEvent::IE_Released,this,&ASelectPlayerController::MouseRelese);
}


void ASelectPlayerController::MouseClick()
{
	m_LButtonClick=true;

	if(m_SelectCharacter)
	{
		ACharacterSelectGameMode* GameMode = Cast<ACharacterSelectGameMode>(
				GetWorld()->GetAuthGameMode());

		if(GameMode)
		{
			ASelectPlayer* SelectPlayer = Cast<ASelectPlayer>(m_SelectCharacter);
			
			UCharacterSelectHUD* SelectHUD=GameMode->GetSelectHUD();

			if(SelectHUD)
			{
				SelectHUD->EnableStartButton(true);
				m_SelectJob =SelectPlayer->GetPlayerJob();

				UUEKR2GameInstance* GameInst = Cast<UUEKR2GameInstance>(GetWorld()->GetGameInstance());

				if(GameInst)
				{
					GameInst->SetSelectJob(m_SelectJob);
				}

					
				switch (m_SelectJob)
				{
				case EPlayerJob::Knight:
					SelectHUD->SetKnightStateVisibility(ESlateVisibility::SelfHitTestInvisible);
					SelectHUD->SetInputNameVisibility(ESlateVisibility::SelfHitTestInvisible);
					SelectHUD->SetArcherStateVisibility(ESlateVisibility::Collapsed);
					break;
				case EPlayerJob::Archer:
					SelectHUD->SetArcherStateVisibility(ESlateVisibility::SelfHitTestInvisible);
					SelectHUD->SetInputNameVisibility(ESlateVisibility::SelfHitTestInvisible);
					SelectHUD->SetKnightStateVisibility(ESlateVisibility::Collapsed);
					break;
				case EPlayerJob::Mage:
					break;;
				}
			}
				
		}
	}
	else
	{
		ACharacterSelectGameMode* GameMode = Cast<ACharacterSelectGameMode>(
		GetWorld()->GetAuthGameMode());

		if(GameMode)
		{
			UCharacterSelectHUD* SelectHUD=GameMode->GetSelectHUD();

			if(SelectHUD)
			{
				SelectHUD->EnableStartButton(false);
				SelectHUD->SetKnightStateVisibility(ESlateVisibility::Collapsed);
				SelectHUD->SetArcherStateVisibility(ESlateVisibility::Collapsed);
				SelectHUD->SetInputNameVisibility(ESlateVisibility::Collapsed);
			}
				
		}
	}
	
}
void ASelectPlayerController::MouseRelese()
{
	m_LButtonClick=false;
}
void ASelectPlayerController::Picking()
{
	FHitResult result;
	bool Hit=GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel9,
		false/*복합 충돌 여부*/, result);

	if(Hit)
	{
		//LOG(TEXT("%s"), *result.GetActor()->GetName());
		ASelectPlayer* SelectPlayer = Cast<ASelectPlayer>(result.GetActor());
		if(SelectPlayer)
		{
			if (m_SelectCharacter != SelectPlayer)
			{
				if (m_SelectCharacter)
					m_SelectCharacter->GetMesh()->SetCustomDepthStencilValue(255);

				m_SelectCharacter = SelectPlayer;

				if(SelectPlayer->GetPlayerJob()==EPlayerJob::Knight)
					m_SelectCharacter->GetMesh()->SetCustomDepthStencilValue(1);
				
				if(SelectPlayer->GetPlayerJob()==EPlayerJob::Archer)
					m_SelectCharacter->GetMesh()->SetCustomDepthStencilValue(3);

				if(SelectPlayer->GetPlayerAnimType()==ESelectPlayerAnimType::IdleStart)
					SelectPlayer->SetPlayerAnimSelect();
			}


			
		}
		else
		{
			if(m_SelectCharacter)
			{
				m_SelectCharacter->GetMesh()->SetCustomDepthStencilValue(255);
				m_SelectCharacter = nullptr;
			}
		}
	}
	
	else
	{
		if (m_SelectCharacter)
		{
			m_SelectCharacter->GetMesh()->SetCustomDepthStencilValue(255);
			m_SelectCharacter = nullptr;
		}
	}
}