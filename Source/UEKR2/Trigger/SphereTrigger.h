// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Trigger.h"
#include "SphereTrigger.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API ASphereTrigger : public ATrigger
{
	GENERATED_BODY()
protected:
	ASphereTrigger();
	


	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
