// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "UEKR2/Monster/Monster.h"
#include "RPG_RatAssassin.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API ARPG_RatAssassin : public AMonster
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	ARPG_RatAssassin();

public:
	class AWeapon* m_Weapon;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NormalAttack();

};
