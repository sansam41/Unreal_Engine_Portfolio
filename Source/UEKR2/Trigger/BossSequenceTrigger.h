// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "BoxTrigger.h"
#include "BossSequenceTrigger.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API ABossSequenceTrigger : public ABoxTrigger
{
	GENERATED_BODY()
public:
	ABossSequenceTrigger();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ULevelSequence* m_SequenceAsset;
	
	ULevelSequencePlayer* m_SequencePlayer;

	ALevelSequenceActor* m_SequenceActor;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	public:
	UFUNCTION()
	void TriggerBegin();
	UFUNCTION()
	void TriggerEnd();	
};
