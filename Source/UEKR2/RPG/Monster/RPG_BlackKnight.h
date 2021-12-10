// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "UEKR2/Monster/Monster.h"
#include "RPG_BlackKnight.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API ARPG_BlackKnight : public AMonster
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	ARPG_BlackKnight();
	class AWeapon* m_Weapon;
	class AWeapon* m_Shield;
	float Skill1Distance;
	float Skill1Delay;
	float Skill1Time;
	bool SkillOn;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void NormalAttack();
	
	void Skill1();

};
