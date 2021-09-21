// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Trigger.h"
#include "CapsuleTrigger.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API ACapsuleTrigger : public ATrigger
{
	GENERATED_BODY()
	public:
	ACapsuleTrigger();
	
	protected:

	
	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};