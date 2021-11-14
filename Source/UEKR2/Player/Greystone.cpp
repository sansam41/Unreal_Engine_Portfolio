// Fill out your copyright notice in the Description page of Project Settings.


#include "Greystone.h"
#include "PlayerAnim.h"
#include "../Effect/NormalEffect.h"
#include "Weapon.h"
#include "UEKR2/Effect/GreystoneSkill3Decal.h"
#include "UEKR2/Skill/Meteor.h"
#include "../Effect/GhostTrail.h"

AGreystone::AGreystone()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	GreystoneAsset(TEXT("SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Skins/WhiteTiger/Meshes/Greystone_WhiteTiger.Greystone_WhiteTiger'"));

	// GetMesh() : CharacterŬ������ ��������ִ� SkeletalMeshComponent�� ������ �Լ��̴�.
	if (GreystoneAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(GreystoneAsset.Object);
		m_PlayerMesh = GreystoneAsset.Object;
	}
	static ConstructorHelpers::FClassFinder<UAnimInstance>	GreystoneAnimAsset(TEXT("AnimBlueprint'/Game/Player/BPGreystoneAnim.BPGreystoneAnim_C'"));

	if (GreystoneAnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(GreystoneAnimAsset.Class);

	static ConstructorHelpers::FObjectFinder<UAnimMontage>	Attack1Asset(TEXT("AnimMontage'/Game/Player/AMGreystoneAttack1.AMGreystoneAttack1'"));

	if (Attack1Asset.Succeeded())
		m_AttackMontageArray.Add(Attack1Asset.Object);

	static ConstructorHelpers::FObjectFinder<UAnimMontage>	Attack2Asset(TEXT("AnimMontage'/Game/Player/AMGreystoneAttack2.AMGreystoneAttack2'"));

	if (Attack2Asset.Succeeded())
		m_AttackMontageArray.Add(Attack2Asset.Object);

	static ConstructorHelpers::FObjectFinder<UAnimMontage>	Attack3Asset(TEXT("AnimMontage'/Game/Player/AMGreystoneAttack3.AMGreystoneAttack3'"));

	if (Attack3Asset.Succeeded())
		m_AttackMontageArray.Add(Attack3Asset.Object);

	static ConstructorHelpers::FObjectFinder<UAnimMontage>	Attack4Asset(TEXT("AnimMontage'/Game/Player/AMGreystoneAttack4.AMGreystoneAttack4'"));

	if (Attack4Asset.Succeeded())
		m_AttackMontageArray.Add(Attack4Asset.Object);

	static ConstructorHelpers::FObjectFinder<UAnimMontage>	Skill1Asset(TEXT("AnimMontage'/Game/Player/AMGreystoneSkill1.AMGreystoneSkill1'"));
	if (Skill1Asset.Succeeded())
		m_SkillMontageArray.Add(Skill1Asset.Object);

	static ConstructorHelpers::FObjectFinder<UAnimMontage>	Skill2Asset(TEXT("AnimMontage'/Game/Player/AMGreystoneSkill2.AMGreystoneSkill2'"));
	if (Skill2Asset.Succeeded())
		m_SkillMontageArray.Add(Skill2Asset.Object);
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage>	Skill3Asset(TEXT("AnimMontage'/Game/Player/AMGreystoneSkill3.AMGreystoneSkill3'"));
	if (Skill2Asset.Succeeded())
		m_SkillMontageArray.Add(Skill3Asset.Object);
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage>	Skill3FireAsset(TEXT("AnimMontage'/Game/Player/AMGreystoneSkill3Fire.AMGreystoneSkill3Fire'"));
	if (Skill3FireAsset.Succeeded())
		m_Skill3FireMontage = Skill3FireAsset.Object;

	static ConstructorHelpers::FClassFinder<AActor>	Skill1Class(
		TEXT("Blueprint'/Game/Player/Greystone/BPGreystoneSkill_1.BPGreystoneSkill_1_C'"));
	if (Skill1Class.Succeeded())
		m_Skill1Class = Skill1Class.Class;

	static ConstructorHelpers::FClassFinder<AActor>	Skill2Class(
		TEXT("Blueprint'/Game/Player/Greystone/BPGreystoneSkill_2.BPGreystoneSkill_2_C'"));

	if (Skill2Class.Succeeded())
		m_Skill2Class = Skill2Class.Class;
	
	static ConstructorHelpers::FClassFinder<AActor>	Skill3Class(
		TEXT("Blueprint'/Game/Player/Greystone/BPGreystoneSkill_3.BPGreystoneSkill_3_C'"));

	if (Skill3Class.Succeeded())
		m_Skill3Class = Skill3Class.Class;


	static ConstructorHelpers::FObjectFinder<UAnimMontage> FallRecoveryAsset(TEXT("AnimMontage'/Game/Player/AMGreystoneFallRecovery.AMGreystoneFallRecovery'"));

	if(FallRecoveryAsset.Succeeded())
	{
		m_FallRecoveryMontage	= FallRecoveryAsset.Object;
		
		m_FallRecoveryMontage->BlendIn.SetBlendOption(EAlphaBlendOption::Cubic);
		m_FallRecoveryMontage->BlendIn.SetBlendTime(0.1f);

				
		m_FallRecoveryMontage->BlendOut.SetBlendOption(EAlphaBlendOption::Cubic);
		m_FallRecoveryMontage->BlendOut.SetBlendTime(0.1f);
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> TrailAsset(TEXT("ParticleSystem'/Game/Particle/PSPlayerTrail.PSPlayerTrail'"));

	if(TrailAsset.Succeeded())
		m_Trail->SetTemplate(TrailAsset.Object);

	
	m_AttackIndex = 0;

	m_PlayerInfo.Name = TEXT("Greystone");
	m_PlayerInfo.Job = EPlayerJob::Knight;
	m_PlayerInfo.Attack = 80;
	m_PlayerInfo.Armor = 20;
	m_PlayerInfo.HP = 500;
	m_PlayerInfo.HPMax = 500;
	m_PlayerInfo.MP = 100;
	m_PlayerInfo.MPMax = 100;
	m_PlayerInfo.AttackDistance = 200.f;
	m_PlayerInfo.AttackSpeed = 1.f;
	m_PlayerInfo.AttackAngle = 22.5f;
	m_PlayerInfo.MoveSpeed = 600.f;

	m_OnSkill3=false;

	m_OnGhostTrail = false;
	m_GhostTrailTime = 0.3f;
	m_GhostTrailTimeAcc = 0.f;
}

// Called when the game starts or when spawned
void AGreystone::BeginPlay()
{
	Super::BeginPlay();
/*
	// 등 뒤 무기
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	m_Weapon=GetWorld()->SpawnActor<AWeapon>(AWeapon::StaticClass(),
		FVector(0.f,0.f,70.f),FRotator(0.f,90.f,180.f),param
		);


	m_Weapon->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("BackWeapon"));

	m_Weapon->SetMesh("SkeletalMesh'/Game/InfinityBladeWeapons/Weapons/Blade/Swords/Blade_BlackKnight/SK_Blade_BlackKnight.SK_Blade_BlackKnight'");
*/
}

// Called every frame
void AGreystone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(m_OnSkill3)
	{
		
		FHitResult result;
		bool Hit = GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursor(
			ECollisionChannel::ECC_GameTraceChannel5,false/*복합 충돌 여부*/, result);
		if(Hit)
		{
				
				m_Skill3Decal->SetActorLocation(result.ImpactPoint);
		}
	}
/*
	if(m_OnGhostTrail)
	{
		m_GhostTrailTimeAcc += DeltaTime;
		if(m_GhostTrailTimeAcc >= m_GhostTrailTime)
		{
			m_GhostTrailTimeAcc -= m_GhostTrailTime;

			FActorSpawnParameters param;
			param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			// Ghost Trail 생성
			AGhostTrail* Trail = GetWorld()->SpawnActor<AGhostTrail>(AGhostTrail::StaticClass(),
				GetMesh()->GetComponentLocation(),
				GetMesh()->GetComponentRotation(),
				param);

			Trail->SetMesh(m_PlayerMesh);
			Trail->CopyAnimation(GetMesh());
		}
	}*/
	
}

// Called to bind functionality to input
void AGreystone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}




void AGreystone::Attack()
{
	if(m_OnSkill3)
	{
		UseSkillFire(2);
		m_Skill3Decal->Destroy();
		if (!m_AnimInstance->Montage_IsPlaying(m_Skill3FireMontage))
		{
			m_AnimInstance->Montage_SetPosition(m_Skill3FireMontage, 0.f);
			m_AnimInstance->Montage_Play(m_Skill3FireMontage);

			
			// Ghost Trail
			OnGhostTrail();
		}
		m_AttackEnable = false;
		m_OnSkill3=false;

	}
	else
	{
		if(!m_AnimInstance->Montage_IsPlaying(m_AttackMontageArray[m_AttackIndex]))
		{
			m_AnimInstance->Montage_SetPosition(m_AttackMontageArray[m_AttackIndex], 0.f);
			m_AnimInstance->Montage_Play(m_AttackMontageArray[m_AttackIndex]);
			m_AnimInstance->SetAttackEnable(true);

			m_AttackIndex = (m_AttackIndex + 1) % m_AttackMontageArray.Num();
		}
	}
}

void AGreystone::Skill1()
{
	if (!m_AnimInstance->Montage_IsPlaying(m_SkillMontageArray[0]))
	{
		m_AnimInstance->Montage_SetPosition(m_SkillMontageArray[0], 0.f);
		m_AnimInstance->Montage_Play(m_SkillMontageArray[0]);
	}
}

void AGreystone::Skill2()
{
	// 0�� ���� ����� ����� �ȵǰ� �ִٸ� ����� �����ش�.
	if (!m_AnimInstance->Montage_IsPlaying(m_SkillMontageArray[1]))
	{
		m_AnimInstance->Montage_SetPosition(m_SkillMontageArray[1], 0.f);
		m_AnimInstance->Montage_Play(m_SkillMontageArray[1]);
	}
}

void AGreystone::Skill3()
{
	
	// 0�� ���� ����� ����� �ȵǰ� �ִٸ� ����� �����ش�.
	if (!m_AnimInstance->Montage_IsPlaying(m_SkillMontageArray[2]))
	{
		m_AnimInstance->Montage_SetPosition(m_SkillMontageArray[2], 0.f);
		m_AnimInstance->Montage_Play(m_SkillMontageArray[2]);

	}
	
}

void AGreystone::NormalAttack()
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

void AGreystone::AttackEnd()
{
	Super::AttackEnd();

	m_AttackIndex = 0;
}

void AGreystone::UseSkill(int32 Index)
{
	switch (Index)
	{
		case 0:
		{
			AGreystoneSkill1* Skill = GetWorld()->SpawnActor<AGreystoneSkill1>(m_Skill1Class,
				GetActorLocation() + GetActorForwardVector() * 100.f,
				GetActorRotation());
			break;
		}
		case 1:
		{
			AGreystoneSkill2* Skill1 = GetWorld()->SpawnActor<AGreystoneSkill2>(m_Skill2Class,
				GetActorLocation() + GetActorForwardVector() * 100.f,
				GetActorRotation());
			AGreystoneSkill2* Skill2 = GetWorld()->SpawnActor<AGreystoneSkill2>(m_Skill2Class,
				GetActorLocation() + GetActorForwardVector() * 100.f + GetActorRightVector() * 50.f,
				GetActorRotation()+FRotator(0.f,20.f,0.f));
	
			AGreystoneSkill2* Skill3 = GetWorld()->SpawnActor<AGreystoneSkill2>(m_Skill2Class,
				GetActorLocation() + GetActorForwardVector() * 100.f + GetActorRightVector() * -50.f,
				GetActorRotation()+FRotator(0.f,-20.f,0.f));
			break;
		}
		case 2:
		{
			m_OnSkill3=true;
			
			FActorSpawnParameters param;
			param.SpawnCollisionHandlingOverride=ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			
			m_Skill3Decal = GetWorld()->SpawnActor<AGreystoneSkill3Decal>(AGreystoneSkill3Decal::StaticClass(),
				GetActorLocation()+FVector(0.f,0.f,0.f),
				FRotator::ZeroRotator,param);
				
			FVector2D Screen=FVector2D::ZeroVector;
			GetWorld()->GetFirstPlayerController()->ProjectWorldLocationToScreen(m_Skill3Decal->GetActorLocation(),Screen);
			GetWorld()->GetFirstPlayerController()->SetMouseLocation(Screen.X,Screen.Y);
			break;
		}
	break;
	}
}
void AGreystone::UseSkillFire(int32 Index)
{
	switch(Index)
	{
		case 0:
			break;
		case 1:
			break;
		case 2:
			// fire skill
			FActorSpawnParameters param;
			param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			AMeteor* Meteor = GetWorld()->SpawnActor<AMeteor>(m_Skill3Class,
			m_Skill3Decal->GetActorLocation()+FVector(0.f,0.f,1500.f),
			FRotator::ZeroRotator,param);
			break;
	}
}


void AGreystone::AttackCombo() {

}