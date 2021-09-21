// Fill out your copyright notice in the Description page of Project Settings.


#include "Wraith.h"
#include "PlayerAnim.h"
#include "../Effect/NormalEffect.h"
#include "UEKR2/Effect/MinionGunnerBullet.h"
#include "UEKR2/Effect/WraithBullet.h"

AWraith::AWraith()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	WraithAsset(TEXT("SkeletalMesh'/Game/ParagonWraith/Characters/Heroes/Wraith/Skins/LunarOps/Meshes/Wraith_LunarOps.Wraith_LunarOps'"));
	
	if (WraithAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(WraithAsset.Object);

	static ConstructorHelpers::FClassFinder<UAnimInstance>	WraithAnimAsset(TEXT("AnimBlueprint'/Game/Player/BPWraithAnim.BPWraithAnim_C'"));

	if (WraithAnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(WraithAnimAsset.Class);

	static ConstructorHelpers::FObjectFinder<UAnimMontage>	Attack1Asset(TEXT("AnimMontage'/Game/Player/AMWraithAttack1.AMWraithAttack1'"));

	if (Attack1Asset.Succeeded())
		m_AttackMontageArray.Add(Attack1Asset.Object);
	/*
	static ConstructorHelpers::FObjectFinder<UAnimMontage>	Skill1Asset(TEXT("AnimMontage'/Game/Player/AMGreystoneSkill1.AMGreystoneSkill1'"));
	if (Skill1Asset.Succeeded())
		m_SkillMontageArray.Add(Skill1Asset.Object);

	static ConstructorHelpers::FObjectFinder<UAnimMontage>	Skill2Asset(TEXT("AnimMontage'/Game/Player/AMGreystoneSkill2.AMGreystoneSkill2'"));
	if (Skill2Asset.Succeeded())
		m_SkillMontageArray.Add(Skill2Asset.Object);

	
	 static ConstructorHelpers::FClassFinder<AActor>	Skill1Class(
		TEXT("Blueprint'/Game/Player/Greystone/BPGreystoneSkill_1.BPGreystoneSkill_1_C'"));
	if (Skill1Class.Succeeded())
		m_Skill1Class = Skill1Class.Class;
		*/


		
	m_AttackIndex = 0;

	m_PlayerInfo.Name = TEXT("Wraith");
	m_PlayerInfo.Job = EPlayerJob::Archer;
	m_PlayerInfo.Attack = 120;
	m_PlayerInfo.Armor = 20;
	m_PlayerInfo.HP = 500;
	m_PlayerInfo.HPMax = 500;
	m_PlayerInfo.MP = 100;
	m_PlayerInfo.MPMax = 100;
	m_PlayerInfo.AttackDistance = 200.f;
	m_PlayerInfo.AttackSpeed = 1.f;
	m_PlayerInfo.AttackAngle = 22.5f;
	m_PlayerInfo.MoveSpeed = 600.f;
}

// Called when the game starts or when spawned
void AWraith::BeginPlay()
{

	Super::BeginPlay();

}

// Called every frame
void AWraith::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AWraith::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}




void AWraith::Attack()
{
	if (!m_AnimInstance->Montage_IsPlaying(m_AttackMontageArray[m_AttackIndex]))
	{
		m_AnimInstance->Montage_SetPosition(m_AttackMontageArray[m_AttackIndex], 0.f);
		m_AnimInstance->Montage_Play(m_AttackMontageArray[m_AttackIndex]);
		m_AnimInstance->SetAttackEnable(true);

		m_AttackIndex = (m_AttackIndex + 1) % m_AttackMontageArray.Num();
	}
}

void AWraith::Skill1()
{

}



void AWraith::NormalAttack()
{
	Super::NormalAttack();

	FVector MuzzleLoc=GetMesh()->GetSocketLocation(TEXT("Muzzle_01"));
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AWraithBullet* Bullet = GetWorld()->SpawnActor<AWraithBullet>(
		AWraithBullet::StaticClass(),MuzzleLoc,GetActorRotation(),param);

	Bullet->SetAttack(m_PlayerInfo.Attack);
	Bullet->SetOwner(this);
}

void AWraith::AttackEnd()
{
	Super::AttackEnd();

	m_AttackIndex = 0;
}

void AWraith::UseSkill(int32 Index)
{
}


void AWraith::AttackCombo()
{
}