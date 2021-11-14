// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "UserCharacter.h"
#include "UserKnightCharacter.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API AUserKnightCharacter : public AUserCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUserKnightCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};