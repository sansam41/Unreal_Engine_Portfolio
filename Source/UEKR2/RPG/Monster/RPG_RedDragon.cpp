// Fill out your copyright notice in the Description page of Project Settings.


#include "RPG_RedDragon.h"

#include "Physics/ImmediatePhysics/ImmediatePhysicsPhysX/ImmediatePhysicsActor_PhysX.h"
#include "UEKR2//Effect/NormalEffect.h"
#include "UEKR2/Effect/MinionGunnerBullet.h"
#include "UEKR2/Effect/RedDragonFire.h"
#include "UEKR2/Player/Weapon.h"


// Sets default values
ARPG_RedDragon::ARPG_RedDragon()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/FourEvilDragonsHP/Meshes/DragonTheUsurper/DragonTheUsurperSK.DragonTheUsurperSK'"));

	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	//static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("AnimBlueprint'/Game/Monster/BPMinionWarriorAnim.BPMinionWarriorAnim_C'"));
	//if (AnimAsset.Succeeded())
	//	GetMesh()->SetAnimInstanceClass(AnimAsset.Class);

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("AnimBlueprint'/Game/Monster/RPG/BP_BlackKnightAnim.BP_BlackKnightAnim_C'"));
	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);

	m_MonsterInfoName = TEXT("RedDragon");
	
	m_DropItemNameArray.Add(TEXT("BF대검"));
	m_DropItemNameArray.Add(TEXT("HP포션"));
	m_Boss=true;
	
	m_BattleStart = true;
	AttackDelay = 1.5f;
	AttackOn = false;
	
	Skill1Distance = 1000.f;
	Skill1Delay = 10.f;
	Skill2Damage = m_MonsterInfo.Attack*1.5f;
	Skill1On = false;
	
	Skill2Distance = 1500.f;
	Skill2Delay = 15.f;
	Skill2On = false;
	Skill2Damage = m_MonsterInfo.Attack;
	Skill2Cnt=0;
}

// Called when the game starts or when spawned
void ARPG_RedDragon::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;


}

// Called every frame
void ARPG_RedDragon::Tick(float DeltaTime)
{
	Skill1Time +=DeltaTime;
	if(Skill1Time>Skill1Delay||Skill1On)
	{
		Skill1Time = 0;
		Skill1On = true;
	}
	
	AttackTime +=DeltaTime;
	if(AttackTime>AttackDelay||AttackOn)
	{
		AttackTime = 0;
		AttackOn = true;
	}

	Skill2Time +=DeltaTime;
	if(Skill2Time>Skill2Delay||Skill2On)
	{
		Skill2Time = 0;
		Skill2On = true;
	}

	Super::Tick(DeltaTime);

}

float ARPG_RedDragon::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float temp = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (m_MonsterInfo.HP <= 0)
	{
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	return temp;
}


void ARPG_RedDragon::NormalAttack()
{
	// 타격 이펙트 처리
	FVector	Forward = GetActorForwardVector();
	FVector	Up = GetActorUpVector();
	FVector	MonsterLoc = GetActorLocation() - Up * 100.f;

	FCollisionQueryParams	params(NAME_None, false, this);

	// 근접공격
	FHitResult	result;
	bool Sweep = GetWorld()->SweepSingleByChannel(result, MonsterLoc,
		MonsterLoc + Forward * m_MonsterInfo.AttackDistance, FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel7,
		FCollisionShape::MakeSphere(30.f),
		params);


#if ENABLE_DRAW_DEBUG

	FColor	DrawColor = Sweep ? FColor::Red : FColor::Green;
	FVector Center = MonsterLoc + Forward * m_MonsterInfo.AttackDistance * 0.5f- Up*100.f;;
	DrawDebugCapsule(GetWorld(),Center, m_MonsterInfo.AttackDistance*0.5f,
		30.f,FRotationMatrix::MakeFromZ(Forward).ToQuat(),DrawColor,false,1.f);

#endif

	if(Sweep)
	{
		FActorSpawnParameters	param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(),
			result.ImpactPoint, result.ImpactNormal.Rotation(), param);


		Effect->LoadParticle(TEXT("ParticleSystem'/Game/AdvancedMagicFX13/Particles/P_ky_impact.P_ky_impact'"));


		Effect->LoadSound(TEXT("SoundWave'/Game/Sound/Attack.Attack'"));

		// 데미지를 전달한다.
		FDamageEvent DmgEvent;
		result.GetActor()->TakeDamage(m_MonsterInfo.Attack, DmgEvent, GetController(),this);
	}
	
}

void ARPG_RedDragon::Skill1Fire()
{
	// 타격 이펙트 처리
	FVector	Forward = GetActorForwardVector();
	FVector	Up = GetActorUpVector();
	FVector	MonsterLoc = GetActorLocation() - Up * 100.f;
	
	FCollisionQueryParams	params(NAME_None, false, this);

	// 근접공격
	FHitResult	result;
	bool Sweep = GetWorld()->SweepSingleByChannel(result, MonsterLoc,
		MonsterLoc + Forward * Skill1Distance, FRotationMatrix::MakeFromZ(Forward).ToQuat(),
		ECollisionChannel::ECC_GameTraceChannel7,
		FCollisionShape::MakeCapsule(80.f,Skill1Distance*0.5f),
		params);

	
	#if ENABLE_DRAW_DEBUG
	FColor	DrawColor = Sweep ? FColor::Red : FColor::Green;
	FVector Center = MonsterLoc + Forward * Skill1Distance * 0.5f - Up*100.f;
	DrawDebugCapsule(GetWorld(),Center, Skill1Distance*0.5f,
	80.f,FRotationMatrix::MakeFromZ(Forward).ToQuat(),DrawColor,false,1.f);

	#endif
	
	if(Sweep)
	{
		FActorSpawnParameters	param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(),
			result.ImpactPoint, result.ImpactNormal.Rotation(), param);
		
		PrintViewport(1.f,FColor::Red,result.Actor->GetName());
		Effect->LoadParticle(TEXT("ParticleSystem'/Game/AdvancedMagicFX13/Particles/P_ky_impact.P_ky_impact'"));


		Effect->LoadSound(TEXT("SoundWave'/Game/Sound/Attack.Attack'"));

		// 데미지를 전달한다.
		FDamageEvent DmgEvent;
		result.GetActor()->TakeDamage(Skill1Damage, DmgEvent, GetController(),this);
	}
	
}

void ARPG_RedDragon::Skill2Fire()
{
	
	FVector SkillLoc=GetMesh()->GetSocketLocation(TEXT("Head"));
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	
	
	ARedDragonFire* Skill1 = GetWorld()->SpawnActor<ARedDragonFire>(ARedDragonFire::StaticClass(),
	SkillLoc + GetActorForwardVector() * 100.f,
	GetActorRotation()+FRotator(0.f,50.f-25.f*Skill2Cnt,0.f),param);
	ARedDragonFire* Skill2 = GetWorld()->SpawnActor<ARedDragonFire>(ARedDragonFire::StaticClass(),
		SkillLoc + GetActorForwardVector() * 100.f + GetActorRightVector() * 50.f,
		GetActorRotation()+FRotator(0.f,70.f-25.f*Skill2Cnt,0.f),param);
	ARedDragonFire* Skill3 = GetWorld()->SpawnActor<ARedDragonFire>(ARedDragonFire::StaticClass(),
		SkillLoc + GetActorForwardVector() * 100.f + GetActorRightVector() * 25.f,
		GetActorRotation()+FRotator(0.f,60.f-25.f*Skill2Cnt,0.f),param);
	ARedDragonFire* Skill4 = GetWorld()->SpawnActor<ARedDragonFire>(ARedDragonFire::StaticClass(),
		SkillLoc + GetActorForwardVector() * 100.f + GetActorRightVector() * -25.f,
		GetActorRotation()+FRotator(0.f,40.f-25.f*Skill2Cnt,0.f),param);
	ARedDragonFire* Skill5 = GetWorld()->SpawnActor<ARedDragonFire>(ARedDragonFire::StaticClass(),
		SkillLoc + GetActorForwardVector() * 100.f + GetActorRightVector() * -50.f,
		GetActorRotation()+FRotator(0.f,30.f-25.f*Skill2Cnt,0.f),param);

	
	ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(),
	SkillLoc,GetActorRotation(),param);


	Effect->LoadSound(TEXT("SoundWave'/Game/Sound/FireBall.FireBall'"));
	
	Skill1->SetAttack(Skill2Damage);
	Skill1->SetOwner(this);
	Skill2->SetAttack(Skill2Damage);
	Skill2->SetOwner(this);
	Skill3->SetAttack(Skill2Damage);
	Skill3->SetOwner(this);
	Skill4->SetAttack(Skill2Damage);
	Skill4->SetOwner(this);
	Skill5->SetAttack(Skill2Damage);
	Skill5->SetOwner(this);
	Skill2Cnt++;
	if(Skill2Cnt==5)
		Skill2Cnt = 0;
}

