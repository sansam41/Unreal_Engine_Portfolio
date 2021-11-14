// Fill out your copyright notice in the Description page of Project Settings.


#include "BossSequenceTrigger.h"


ABossSequenceTrigger::ABossSequenceTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_SequenceAsset = nullptr;
	m_SequencePlayer = nullptr;
	
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
	if(m_SequenceAsset)
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
	}
}

void ABossSequenceTrigger::TriggerEnd()
{
	
}