// Fill out your copyright notice in the Description page of Project Settings.


#include "RPG_RedDragonAnim.h"
#include "Monster.h"
#include "UEKR2/RPG/Monster/RPG_RedDragon.h"

URPG_RedDragonAnim::URPG_RedDragonAnim() {
	m_OnGround = true;
	m_AnimType = EMonsterAnimType::Idle;

	m_Hit=0.f;
}

void URPG_RedDragonAnim::NativeInitializeAnimation() {
	Super::NativeInitializeAnimation();
}


void URPG_RedDragonAnim::NativeUpdateAnimation(float DeltaSeconds) {
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

void URPG_RedDragonAnim::AnimNotify_Attack()
{
	AMonster* Monster = Cast<AMonster>(TryGetPawnOwner());
	if (Monster)
	{
		Monster->NormalAttack();
	}
}


void URPG_RedDragonAnim::AnimNotify_AttackEnd()
{
	AMonster* Monster = Cast<AMonster>(TryGetPawnOwner());
	if (Monster)
	{
		Monster->SetAttackEnd(true);
	}
}

void URPG_RedDragonAnim::AnimNotify_DeathEnd()
{
	AMonster* Monster = Cast<AMonster>(TryGetPawnOwner());
	if (Monster)
	{
		Monster->Death();
	}
}

void URPG_RedDragonAnim::AnimNotify_HitEnd()
{
	m_Hit=0.f;
}

void URPG_RedDragonAnim::AnimNotify_Skill1Fire()
{
	ARPG_RedDragon* Monster = Cast<ARPG_RedDragon>(TryGetPawnOwner());
	Monster->Skill1Fire();
}

void URPG_RedDragonAnim::AnimNotify_Skill2Fire()
{
	ARPG_RedDragon* Monster = Cast<ARPG_RedDragon>(TryGetPawnOwner());
	Monster->Skill2Fire();
}

