// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnimInstance.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EMonsterAnimType : uint8
{
	Idle,
	Walk,
	Run,
	Attack,
	Death,
	Skill,
};

UENUM(BlueprintType)
enum class EMonsterAttackType : uint8
{
	Attack1,
	Attack2,
	Attack3,
	Attack4,
};


UCLASS()
class UEKR2_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UMonsterAnimInstance();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool	m_OnGround;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EMonsterAnimType	m_AnimType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EMonsterAttackType	m_AttackType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float m_Hit;
public:
	EMonsterAnimType GetAnimType() const
	{
		return m_AnimType;
	}

	void ChangeAnimType(EMonsterAnimType Type)
	{
		m_AnimType = Type;
	}

	
	EMonsterAttackType GetAttackType() const
	{
		return m_AttackType;
	}

	void ChangeAttackType(EMonsterAttackType Type)
	{
		m_AttackType = Type;
	}

	void SetHit()
	{
		m_Hit=1.f;
	}
	

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

public:
	UFUNCTION()
	virtual void AnimNotify_Attack();

	UFUNCTION()
	virtual void AnimNotify_AttackEnd();

	UFUNCTION()
	virtual void AnimNotify_DeathEnd();
	
	UFUNCTION()
	virtual void AnimNotify_HitEnd();
};
