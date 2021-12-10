// Fill out your copyright notice in the Description page of Project Settings.


#include "RPG_BlackKnightAnim.h"
#include "Monster.h"
#include "UEKR2/RPG/Monster/RPG_BlackKnight.h"

URPG_BlackKnightAnim::URPG_BlackKnightAnim() {
	m_OnGround = true;
	m_AnimType = EMonsterAnimType::Idle;

	m_Hit=0.f;
}

void URPG_BlackKnightAnim::NativeInitializeAnimation() {
	Super::NativeInitializeAnimation();
}


void URPG_BlackKnightAnim::NativeUpdateAnimation(float DeltaSeconds) {
	Super::NativeUpdateAnimation(DeltaSeconds);

	AMonster* Monster = Cast<AMonster>(TryGetPawnOwner());

	if (Monster) {
		UCharacterMovementComponent* Movement = Monster->GetCharacterMovement();

		if (Movement) {
			bool OnGround = Movement->IsMovingOnGround();

			m_OnGround = OnGround;
		}
	}
}

void URPG_BlackKnightAnim::AnimNotify_Attack()
{
	AMonster* Monster = Cast<AMonster>(TryGetPawnOwner());
	if (Monster)
	{
		Monster->NormalAttack();
	}
}


void URPG_BlackKnightAnim::AnimNotify_AttackEnd()
{
	AMonster* Monster = Cast<AMonster>(TryGetPawnOwner());
	if (Monster)
	{
		Monster->SetAttackEnd(true);
	}
}

void URPG_BlackKnightAnim::AnimNotify_DeathEnd()
{
	AMonster* Monster = Cast<AMonster>(TryGetPawnOwner());
	if (Monster)
	{
		Monster->Death();
	}
}

void URPG_BlackKnightAnim::AnimNotify_HitEnd()
{
	m_Hit=0.f;
}

void URPG_BlackKnightAnim::AnimNotify_Skill1()
{
	ARPG_BlackKnight* Monster = Cast<ARPG_BlackKnight>(TryGetPawnOwner());
	Monster->Skill1();
}
