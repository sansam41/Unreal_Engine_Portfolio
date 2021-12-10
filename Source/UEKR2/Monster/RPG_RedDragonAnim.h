// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "MonsterAnimInstance.h"
#include "RPG_RedDragonAnim.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API URPG_RedDragonAnim : public UMonsterAnimInstance
{
	GENERATED_BODY()
	public:
	URPG_RedDragonAnim();

	protected:
	

	public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);
	
	public:
	virtual void AnimNotify_Attack();

	virtual void AnimNotify_AttackEnd();

	virtual void AnimNotify_DeathEnd();
	
	virtual void AnimNotify_HitEnd();

	UFUNCTION()
	void AnimNotify_Skill1Fire();
	UFUNCTION()
	void AnimNotify_Skill2Fire();
};
