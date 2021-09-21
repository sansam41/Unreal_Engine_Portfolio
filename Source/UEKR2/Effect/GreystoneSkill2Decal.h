// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "EffectDecal.h"
#include "GreystoneSkill2Decal.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API AGreystoneSkill2Decal : public AEffectDecal
{
	GENERATED_BODY()
public:
	AGreystoneSkill2Decal();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
