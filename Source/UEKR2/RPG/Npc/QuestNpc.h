// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "../../RPG/Npc/NpcBase.h"
#include "QuestNpc.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API AQuestNpc : public ANpcBase
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AQuestNpc();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:

public:
	void NextQuest()
	{
		m_QuestProgress = m_QuestProgress + 1;
	}
	
};
