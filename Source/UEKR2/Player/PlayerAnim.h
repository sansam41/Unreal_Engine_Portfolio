// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnim.generated.h"

UENUM(BlueprintType)
enum class EPlayerAnimType : uint8
{
	Ground,
	Jump,
	Fall,
	Death
};


UCLASS()
class UEKR2_API UPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPlayerAnim();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	m_Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	m_Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool	m_Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool	m_OnGround;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EPlayerAnimType	m_AnimType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	m_FallRecoveryAdditive;

public:
	float GetDirection()
	{
		return m_Direction;
	}

	void SetDirection(float Direction)
	{
		m_Direction = Direction;
	}

	void SetAttackEnable(bool Attack)
	{
		m_Attack = Attack;
	}

	bool IsAttack()	const
	{
		return m_Attack;
	}

	void ChangeAnimType(EPlayerAnimType Type)
	{
		m_AnimType = Type;
	}

	EPlayerAnimType GetAnimType()
	{
		return m_AnimType;
	}
	

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

public:
	// 노티파이가 호출할 함수를 만들때는 반드시 규칙을 지켜야 한다.
	// AnimNotify_ 를 한 뒤에 노티파이 이름으로 함수를 만들어준다.
	UFUNCTION()
	void AnimNotify_AttackEnd();

	UFUNCTION()
	void AnimNotify_NormalAttack();

	UFUNCTION()
	void AnimNotify_AttackCombo();

	UFUNCTION()
	void AnimNotify_JumpStart();
	
	UFUNCTION()
	void AnimNotify_JumpEnd();
	
	UFUNCTION()
	void AnimNotify_FallEnd();
		
	UFUNCTION()
	void AnimNotify_FallRecoveryEnd();

	UFUNCTION()
	void AnimNotify_SkillFire1();

	UFUNCTION()
	void AnimNotify_SkillFire2();
	UFUNCTION()
	void AnimNotify_OnMagic();
	UFUNCTION()
	void AnimNotify_SkillEnd();
	UFUNCTION()
	void AnimNotify_Skill3Fire();
	UFUNCTION()
	void AnimNotify_RightStep();
	UFUNCTION()
	void AnimNotify_LeftStep();
	UFUNCTION()
	void AnimNotify_GhostTrailEnd();
	UFUNCTION()
	void AnimNotify_IdleStart();

};
