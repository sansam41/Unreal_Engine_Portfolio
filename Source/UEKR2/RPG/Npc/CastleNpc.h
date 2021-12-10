// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "../../RPG/Npc/NpcBase.h"
#include "CastleNpc.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API ACastleNpc : public ANpcBase
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	ACastleNpc();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	bool m_key;
	bool m_checked;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	void NextDialogue()
	{
		m_DialogueProgress = m_DialogueProgress + 1;
	}

	void MovePlayer();
};
