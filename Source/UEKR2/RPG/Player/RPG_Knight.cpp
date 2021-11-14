// Fill out your copyright notice in the Description page of Project Settings.


#include "RPG_Knight.h"
#include "RPGPlayerAnim.h"
#include "UEKR2/Effect/NormalEffect.h"
#include "UEKR2/Player/Weapon.h"

ARPG_Knight::ARPG_Knight()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	KnightAsset(TEXT("SkeletalMesh'/Game/ModularRPGHeroesPolyart/Meshes/OneMeshCharacters/KnightSK.KnightSK'"));
	
	if (KnightAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(KnightAsset.Object);
		m_PlayerMesh = KnightAsset.Object;
	}
	
	static ConstructorHelpers::FClassFinder<UAnimInstance>	KnightAnimAsset(TEXT("AnimBlueprint'/Game/Player/RPG/BP_RPGKnightAnim.BP_RPGKnightAnim_C'"));

	if (KnightAnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(KnightAnimAsset.Class);

	static ConstructorHelpers::FObjectFinder<UAnimMontage>	Attack1Asset(TEXT("AnimMontage'/Game/Player/RPG/AM_KnightAttack1.AM_KnightAttack1'"));

	if (Attack1Asset.Succeeded())
		m_AttackMontageArray.Add(Attack1Asset.Object);
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage>	Attack2sset(TEXT("AnimMontage'/Game/Player/RPG/AM_KnightAttack2.AM_KnightAttack2'"));

	if (Attack2sset.Succeeded())
		m_AttackMontageArray.Add(Attack2sset.Object);
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage>	Attack3Asset(TEXT("AnimMontage'/Game/Player/RPG/AM_KnightAttack3.AM_KnightAttack3'"));

	if (Attack3Asset.Succeeded())
		m_AttackMontageArray.Add(Attack3Asset.Object);
	/*
	static ConstructorHelpers::FObjectFinder<UAnimMontage>	Skill1Asset(TEXT("AnimMontage'/Game/Player/AMWraithSkill1.AMWraithSkill1'"));
	if (Skill1Asset.Succeeded())
		m_SkillMontageArray.Add(Skill1Asset.Object);
   */

/*	
	 static ConstructorHelpers::FClassFinder<AActor>	Skill1Class(TEXT("Blueprint'/Game/Player/Wraith/BPWraithSkill1.BPWraithSkill1_C'"));
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
void ARPG_Knight::BeginPlay()
{

	Super::BeginPlay();
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	m_Weapon=GetWorld()->SpawnActor<AWeapon>(AWeapon::StaticClass(),
		FVector(0.f,0.f,0.f),FRotator(0.f,0.f,0.f),param
		);


	m_Weapon->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("RightWeaponShield"));

	m_Weapon->SetMesh("SkeletalMesh'/Game/Player/RPG/Weapons/Sword01SM.Sword01SM_Sword01SM'");

	
	m_Shield=GetWorld()->SpawnActor<AWeapon>(AWeapon::StaticClass(),
		FVector(0.f,0.f,0.f),FRotator(0.f,0.f,0.f),param
		);


	m_Shield->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("LeftWeaponShield"));

	m_Shield->SetMesh("SkeletalMesh'/Game/Player/RPG/Weapons/Shield01SM.Shield01SM_Shield01SM'");
}

// Called every frame
void ARPG_Knight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ARPG_Knight::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}




void ARPG_Knight::Attack()
{
	if(!m_AnimInstance->Montage_IsPlaying(m_AttackMontageArray[m_AttackIndex]))
	{
		m_AnimInstance->Montage_SetPosition(m_AttackMontageArray[m_AttackIndex], 0.f);
		m_AnimInstance->Montage_Play(m_AttackMontageArray[m_AttackIndex]);
		m_AnimInstance->SetAttackEnable(true);

		m_AttackIndex = (m_AttackIndex + 1) % m_AttackMontageArray.Num();
	}
}

void ARPG_Knight::Skill1()
{
	if (!m_AnimInstance->Montage_IsPlaying(m_SkillMontageArray[0]))
	{
		m_AttackEnable = false;
		SetCasting(true);
		m_AnimInstance->SetAttackEnable(true);
		m_AnimInstance->Montage_SetPosition(m_SkillMontageArray[0], 0.f);
		m_AnimInstance->Montage_Play(m_SkillMontageArray[0]);
	}
}



void ARPG_Knight::NormalAttack()
{
	Super::NormalAttack();

	FVector	PlayerLoc = GetActorLocation();
	FVector	Forward = GetActorForwardVector();

	FCollisionQueryParams	params(NAME_None, false, this);

	
	TArray<FHitResult>	HitResultArray;
	bool Sweep = GetWorld()->SweepMultiByChannel(HitResultArray, PlayerLoc,
		PlayerLoc, FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel3, FCollisionShape::MakeSphere(m_PlayerInfo.AttackDistance),
		params);

	//LOG(TEXT("Attack : %.5f"), 200.f);
	//LOG(TEXT("TestAttack"));
	PrintViewport(1.f, FColor::Yellow, TEXT("Attack"));

	TArray<FHitResult>	CollisionArray;
	if (Sweep)
	{
		for (auto& result : HitResultArray)
		{
			FVector	Dir = result.ImpactPoint - GetActorLocation();

			Dir.Normalize();

			Forward = GetActorForwardVector();
			Forward.Normalize();

			float Dot = FVector::DotProduct(Dir, Forward);
			float Angle = FMath::Acos(Dot);
			Angle = FMath::RadiansToDegrees(Angle);

			if (Angle <= m_PlayerInfo.AttackAngle)
				CollisionArray.Add(result);

			else
			{
			}
		}
	}
#if ENABLE_DRAW_DEBUG

	FColor	DrawColor = CollisionArray.Num() > 0 ? FColor::Red : FColor::Green;

	//DrawDebugSphere(GetWorld(), PlayerLoc, m_PlayerInfo.AttackDistance, 20, DrawColor, false, 1.f);
	DrawDebugCone(GetWorld(), PlayerLoc, GetActorForwardVector(), m_PlayerInfo.AttackDistance,
		FMath::DegreesToRadians(m_PlayerInfo.AttackAngle),
		FMath::DegreesToRadians(m_PlayerInfo.AttackAngle), 20,
		DrawColor, false, 1.f);

#endif

	for (auto& result : CollisionArray)
	{
		FActorSpawnParameters	param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(),
			result.ImpactPoint, result.ImpactNormal.Rotation(), param);

		//Effect->LoadParticle(TEXT("ParticleSystem'/Game/AdvancedMagicFX12/particles/P_ky_hit_thunder.P_ky_hit_thunder'"));
		Effect->LoadParticleAsync(TEXT("HitNormal"));
		
		// Sound
		//Effect->LoadSound(TEXT("SoundWave'/Game/Sound/Fire4.Fire4'"));
		Effect->LoadSoundAsync(TEXT("HitSword"));

		// 데미지를 전달한다.
		FDamageEvent DmgEvent;
		result.GetActor()->TakeDamage(m_PlayerInfo.Attack, DmgEvent, GetController(),this);
	}
}



void ARPG_Knight::AttackEnd()
{
	Super::AttackEnd();

	m_AttackIndex = 0;
}

void ARPG_Knight::UseSkill(int32 Index)
{
	switch (Index)
	{
	case 0:
		{
			

		}
	case 1:
		{
			
		}
	case 2:
		{
		
		}
		break;
	}
}

