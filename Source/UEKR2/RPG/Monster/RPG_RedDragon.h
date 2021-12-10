// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "UEKR2/Monster/Monster.h"
#include "RPG_RedDragon.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API ARPG_RedDragon : public AMonster
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	ARPG_RedDragon();
	
	float	AttackDelay;
	float	AttackTime;
	bool	AttackOn;
	
	float	Skill1Distance;
	float	Skill1Damage;
	float	Skill1Delay;
	float	Skill1Time;
	bool	Skill1On;
	
	float	Skill2Distance;
	float	Skill2Damage;
	float	Skill2Delay;
	float	Skill2Time;
	bool	Skill2On;
	int32	Skill2Cnt;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	void NormalAttack();
	void Skill1Fire();
	void Skill2Fire();

};	
