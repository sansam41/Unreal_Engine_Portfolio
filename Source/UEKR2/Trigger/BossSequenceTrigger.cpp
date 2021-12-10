// Fill out your copyright notice in the Description page of Project Settings.


#include "BossSequenceTrigger.h"

#include "UEKR2/RPG/Player/RPG_PlayerCharacter.h"


ABossSequenceTrigger::ABossSequenceTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_SequenceAsset = nullptr;
	m_SequencePlayer = nullptr;
	m_IsPlayed = false;
	
}

// Called when the game starts or when spawned
void ABossSequenceTrigger::BeginPlay()
{
	Super::BeginPlay();

	m_TriggerBeginDelegate.AddDynamic(this,&ABossSequenceTrigger::TriggerBegin);
	m_TriggerEndDelegate.AddDynamic(this,&ABossSequenceTrigger::TriggerEnd);
	
}

// Called every frame
void ABossSequenceTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void ABossSequenceTrigger::TriggerBegin()
{
	if(m_SequenceAsset&&!m_IsPlayed)
	{
		if(!m_SequencePlayer)
		{
			m_SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
				GetWorld(),m_SequenceAsset,FMovieSceneSequencePlaybackSettings(),
				m_SequenceActor
				);
		}

		PrintViewport(1.f, FColor::Red, TEXT("Hit"));
		m_SequencePlayer->Play();
		ARPG_PlayerCharacter* Player = Cast<ARPG_PlayerCharacter>(m_Other);
		if(Player)
			Player->SetEnableInput(false);
		
	}
}

void ABossSequenceTrigger::TriggerEnd()
{
	if(!m_IsPlayed)
	{
		m_IsPlayed = true;
		ARPG_PlayerCharacter* Player = Cast<ARPG_PlayerCharacter>(m_Other);
		if(Player)
			Player->SetEnableInput(true);
		if(m_Monster)
			m_Monster->m_BattleStart=true;
	}
}