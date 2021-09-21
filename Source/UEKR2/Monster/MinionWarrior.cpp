// Fill out your copyright notice in the Description page of Project Settings.


#include "MinionWarrior.h"
#include "../Effect/NormalEffect.h"


// Sets default values
AMinionWarrior::AMinionWarrior()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/ParagonMinions/Characters/Minions/Down_Minions/Meshes/Minion_Lane_Melee_Dawn.Minion_Lane_Melee_Dawn'"));

	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("AnimBlueprint'/Game/Monster/BPMinionWarriorAnim.BPMinionWarriorAnim_C'"));
	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);

	m_MonsterInfoName = TEXT("MinionWarrior");
	
}

// Called when the game starts or when spawned
void AMinionWarrior::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMinionWarrior::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMinionWarrior::NormalAttack()
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

	
#if ENABLE_DRAW_DEBUG

	FColor	DrawColor = Sweep ? FColor::Red : FColor::Green;

	FVector Center = MonsterLoc + Forward * m_MonsterInfo.AttackDistance * 0.5f;
	DrawDebugCapsule(GetWorld(),Center, m_MonsterInfo.AttackDistance*0.5f,
		30.f,FRotationMatrix::MakeFromZ(Forward).ToQuat(),DrawColor,false,0.5f);

#endif

	if(Sweep)
	{
		FActorSpawnParameters	param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(),
			result.ImpactPoint, result.ImpactNormal.Rotation(), param);


		Effect->LoadParticle(TEXT("ParticleSystem'/Game/AdvancedMagicFX13/Particles/P_ky_flash1.P_ky_flash1'"));


		Effect->LoadSound(TEXT("SoundWave'/Game/Sound/Fire4.Fire4'"));

		// 데미지를 전달한다.
		FDamageEvent DmgEvent;
		result.GetActor()->TakeDamage(m_MonsterInfo.Attack, DmgEvent, GetController(),this);
	}
	
}