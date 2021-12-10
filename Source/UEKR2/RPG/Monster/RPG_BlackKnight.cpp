// Fill out your copyright notice in the Description page of Project Settings.


#include "RPG_BlackKnight.h"
#include "UEKR2//Effect/NormalEffect.h"
#include "UEKR2/Effect/MinionGunnerBullet.h"
#include "UEKR2/Player/Weapon.h"


// Sets default values
ARPG_BlackKnight::ARPG_BlackKnight()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/RPGMonsterWave2PA/Mesh/BlackKnight/BlackKnightSK.BlackKnightSK'"));

	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	//static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("AnimBlueprint'/Game/Monster/BPMinionWarriorAnim.BPMinionWarriorAnim_C'"));
	//if (AnimAsset.Succeeded())
	//	GetMesh()->SetAnimInstanceClass(AnimAsset.Class);

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("AnimBlueprint'/Game/Monster/RPG/BP_BlackKnightAnim.BP_BlackKnightAnim_C'"));
	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);

	m_MonsterInfoName = TEXT("BlackKnight");
	
	m_DropItemNameArray.Add(TEXT("BF대검"));
	m_DropItemNameArray.Add(TEXT("HP포션"));
	m_Boss=true;
	

	Skill1Distance = 500.f;
	Skill1Delay = 6.f;
	SkillOn = false;
}

// Called when the game starts or when spawned
void ARPG_BlackKnight::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	
	m_Weapon=GetWorld()->SpawnActor<AWeapon>(AWeapon::StaticClass(),
	FVector(0.f,0.f,0.f),FRotator(0.f,0.f,0.f),param
	);
	
	m_Weapon->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("AxeSocket"));

	m_Weapon->SetMesh("SkeletalMesh'/Game/Monster/RPG/BlackKnightAxeSM.BlackKnightAxeSM_AxeSM'");

	
	m_Shield=GetWorld()->SpawnActor<AWeapon>(AWeapon::StaticClass(),
	FVector(0.f,0.f,0.f),FRotator(0.f,0.f,0.f),param
	);


	m_Shield->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("ShieldSocket"));

	m_Shield->SetMesh("SkeletalMesh'/Game/Monster/RPG/BlackKnightShieldSM.BlackKnightShieldSM_ShieldSM'");

}

// Called every frame
void ARPG_BlackKnight::Tick(float DeltaTime)
{
	Skill1Time +=DeltaTime;
	if(Skill1Time>Skill1Delay||SkillOn)
	{
		Skill1Time = 0;
		SkillOn = true;
	}
	
	if (m_DissolveEnable)
	{
		m_Weapon->Destroy();
		m_Shield->Destroy();
	}
	Super::Tick(DeltaTime);

}

void ARPG_BlackKnight::NormalAttack()
{
	// 타격 이펙트 처리
	FVector	MonsterLoc = GetActorLocation();
	FVector	Forward = GetActorForwardVector();

	FCollisionQueryParams	params(NAME_None, false, this);

	// 근접공격
	FHitResult	result;
	bool Sweep = GetWorld()->SweepSingleByChannel(result, MonsterLoc,
		MonsterLoc + Forward * m_MonsterInfo.AttackDistance, FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel7,
		FCollisionShape::MakeSphere(30.f),
		params);

/*
#if ENABLE_DRAW_DEBUG

	FColor	DrawColor = Sweep ? FColor::Red : FColor::Green;

	FVector Center = MonsterLoc + Forward * m_MonsterInfo.AttackDistance * 0.5f;
	DrawDebugCapsule(GetWorld(),Center, m_MonsterInfo.AttackDistance*0.5f,
		30.f,FRotationMatrix::MakeFromZ(Forward).ToQuat(),DrawColor,false,0.5f);

#endif
*/
	if(Sweep)
	{
		FActorSpawnParameters	param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(),
			result.ImpactPoint, result.ImpactNormal.Rotation(), param);


		Effect->LoadParticle(TEXT("ParticleSystem'/Game/AdvancedMagicFX13/Particles/P_ky_flash1.P_ky_flash1'"));


		Effect->LoadSound(TEXT("SoundWave'/Game/Sound/Sword1.Sword1'"));

		// 데미지를 전달한다.
		FDamageEvent DmgEvent;
		result.GetActor()->TakeDamage(m_MonsterInfo.Attack, DmgEvent, GetController(),this);
	}
	
}


void ARPG_BlackKnight::Skill1()
{
	FVector SkillLoc=GetActorLocation();
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	
	AMinionGunnerBullet* Skill1 = GetWorld()->SpawnActor<AMinionGunnerBullet>(AMinionGunnerBullet::StaticClass(),
		GetActorLocation() + GetActorForwardVector() * 100.f,
		GetActorRotation(),param);
	
	AMinionGunnerBullet* Skill2 = GetWorld()->SpawnActor<AMinionGunnerBullet>(AMinionGunnerBullet::StaticClass(),
		GetActorLocation() + GetActorForwardVector() * 100.f + GetActorRightVector() * 50.f,
		GetActorRotation()+FRotator(0.f,20.f,0.f),param);
	
	AMinionGunnerBullet* Skill3 = GetWorld()->SpawnActor<AMinionGunnerBullet>(AMinionGunnerBullet::StaticClass(),
		GetActorLocation() + GetActorForwardVector() * 100.f + GetActorRightVector() * -50.f,
		GetActorRotation()+FRotator(0.f,-20.f,0.f),param);

	ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(),
	SkillLoc,GetActorRotation(),param);


	Effect->LoadSound(TEXT("SoundWave'/Game/Sound/ThickLaser.ThickLaser'"));
	
	Skill1->SetAttack(m_MonsterInfo.Attack);
	Skill1->SetOwner(this);
	Skill2->SetAttack(m_MonsterInfo.Attack);
	Skill2->SetOwner(this);
	Skill3->SetAttack(m_MonsterInfo.Attack);
	Skill3->SetOwner(this);


}