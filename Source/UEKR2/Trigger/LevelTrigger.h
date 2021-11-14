// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "BoxTrigger.h"
#include "LevelTrigger.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API ALevelTrigger : public ABoxTrigger
{
	GENERATED_BODY()
public:
	ALevelTrigger();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString m_StreamingLevelName;
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
