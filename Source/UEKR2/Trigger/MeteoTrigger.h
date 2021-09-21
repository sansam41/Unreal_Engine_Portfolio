// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "BoxTrigger.h"
#include "MeteoTrigger.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API AMeteoTrigger : public ABoxTrigger
{
	GENERATED_BODY()

public:
	AMeteoTrigger();
	
protected:

	
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
