// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGPlayerAnim.h"

#include "RPG_Knight.h"
#include "RPG_PlayerCharacter.h"


URPGPlayerAnim::URPGPlayerAnim() {
	m_Direction = 0;
	m_Speed = 0;
	m_Attack = false;
	m_OnGround = true;
	m_AnimType = ERPG_PlayerAnimType::Ground;

}

void URPGPlayerAnim::NativeInitializeAnimation() {
	Super::NativeInitializeAnimation();
}
void URPGPlayerAnim::NativeUpdateAnimation(float DeltaSeconds) {
	Super::NativeUpdateAnimation(DeltaSeconds);

	ARPG_PlayerCharacter* Player = Cast<ARPG_PlayerCharacter>(TryGetPawnOwner());
	if (Player) {
		UCharacterMovementComponent* Movement = Player->GetCharacterMovement();
		
		if (Movement)
		{
			// 속도를 구한다
			m_Speed = Movement->Velocity.Size();

			// 땅을 밟고 있는지 구한다.
			bool OnGround = Movement->IsMovingOnGround();
				
			//if (!m_OnGround && OnGround && Player->IsMoveKey())
			//	m_AnimType = EPlayerAnimType::Ground;
			
			m_OnGround = OnGround;
			
			if(m_OnGround&&m_AnimType==ERPG_PlayerAnimType::Fall)
			{
				m_AnimType=ERPG_PlayerAnimType::JumpEnd;
			}
			else if(!m_OnGround&&m_AnimType!=ERPG_PlayerAnimType::Jump)
			{
				m_AnimType=ERPG_PlayerAnimType::Fall;
			}
		}
	}
}

void URPGPlayerAnim::AnimNotify_AttackEnd() {
	m_Attack = false;
	ARPG_PlayerCharacter* Player = Cast<ARPG_PlayerCharacter>(TryGetPawnOwner());
	if (Player)
		Player->AttackEnd();
}


void URPGPlayerAnim::AnimNotify_NormalAttack() {
	ARPG_PlayerCharacter* Player = Cast<ARPG_PlayerCharacter>(TryGetPawnOwner());
	if (Player)
		Player->NormalAttack();
}

void URPGPlayerAnim::AnimNotify_JumpStart()
{
	ARPG_PlayerCharacter* Player = Cast<ARPG_PlayerCharacter>(TryGetPawnOwner());
	if (Player)
	{
		Player->EnableAttack(false);
	}
}
void URPGPlayerAnim::AnimNotify_JumpStartEnd() {
	m_AnimType = ERPG_PlayerAnimType::Fall;
}

void URPGPlayerAnim::AnimNotify_JumpEnd() {
	ARPG_PlayerCharacter* Player = Cast<ARPG_PlayerCharacter>(TryGetPawnOwner());
	if (Player)
		Player->EnableAttack(true);
	
	m_AnimType = ERPG_PlayerAnimType::Ground;

}



void URPGPlayerAnim::AnimNotify_AttackCombo() {
	ARPG_PlayerCharacter* Player = Cast<ARPG_PlayerCharacter>(TryGetPawnOwner());
	if (Player)
		Player->EnableAttack(true);
}

void URPGPlayerAnim::AnimNotify_SkillFire1() {
	//m_Attack = false;
	ARPG_PlayerCharacter* Player = Cast<ARPG_PlayerCharacter>(TryGetPawnOwner());

	if (Player)
	{
		Player->UseSkill(0);
	}
}

void URPGPlayerAnim::AnimNotify_SkillFire2() {
	//m_Attack = false;
	ARPG_PlayerCharacter* Player = Cast<ARPG_PlayerCharacter>(TryGetPawnOwner());

	if (Player)
	{
		Player->UseSkill(1);
		
	}
}

void URPGPlayerAnim::AnimNotify_OnMagic() {
	ARPG_PlayerCharacter* Player = Cast<ARPG_PlayerCharacter>(TryGetPawnOwner());

	if (Player)
	{
		Player->EnableAttack(true);
		Player->UseSkill(2);
	}
}

void URPGPlayerAnim::AnimNotify_RightStep()
{
	ARPG_PlayerCharacter* Player = Cast<ARPG_PlayerCharacter>(TryGetPawnOwner());
	if(Player)
		Player->FootStep(false);
}
void URPGPlayerAnim::AnimNotify_LeftStep()
{
	ARPG_PlayerCharacter* Player = Cast<ARPG_PlayerCharacter>(TryGetPawnOwner());
	if(Player)
		Player->FootStep(true);
}

void URPGPlayerAnim::AnimNotify_Skill3Fire()
{

}
void URPGPlayerAnim::AnimNotify_SkillEnd()
{
	ARPG_PlayerCharacter* Player = Cast<ARPG_PlayerCharacter>(TryGetPawnOwner());

	if(Player)
	{
		Player->AttackEnd();
		Player->SetCasting(false);
	}
}

void URPGPlayerAnim::AnimNotify_IdleStart()
{
	
}
void URPGPlayerAnim::AnimNotify_HitedEnd()
{
	ARPG_Knight* Player = Cast<ARPG_Knight>(TryGetPawnOwner());

	if(Player)
	{
		Player->m_BeHited =false;
	}
}
void URPGPlayerAnim::AnimNotify_RollEnd()
{
	ARPG_PlayerCharacter* Player = Cast<ARPG_PlayerCharacter>(TryGetPawnOwner());

	if(Player)
	{
		Player->m_Rolling = false;
		Player->GetCharacterMovement()->MaxWalkSpeed /=1.5; 
	}
}