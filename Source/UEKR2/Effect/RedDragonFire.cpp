// Fill out your copyright notice in the Description page of Project Settings.


#include "RedDragonFire.h"
#include "NormalEffect.h"
#include "../Monster/Monster.h"

// Sets default values
ARedDragonFire::ARedDragonFire()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("ParticleSystem'/Game/AdvancedMagicFX12/particles/P_ky_shot_fire.P_ky_shot_fire'"));

	if(ParticleAsset.Succeeded())
		m_Particle->SetTemplate(ParticleAsset.Object);
	
	m_Movement->InitialSpeed=2000.f;

	
	m_Body->SetCollisionProfileName(TEXT("EnemyAttack"));
	m_Particle->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
	
}

// Called when the game starts or when spawned
void ARedDragonFire::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARedDragonFire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ARedDragonFire::StopEvent(const FHitResult& result)
{
	Super::StopEvent(result);

	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(),
		result.ImpactPoint,result.ImpactNormal.Rotation(),param);

	Effect->LoadParticle(TEXT("ParticleSystem'/Game/AdvancedMagicFX12/particles/P_ky_hit_fire.P_ky_hit_fire'"));

	// Sound
	Effect->LoadSound(TEXT("SoundWave'/Game/Sound/FireBallExplosion.FireBallExplosion'"));

	m_Particle->DestroyComponent();

	if(IsValid(m_Owner))
	{
		FDamageEvent	DmgEvent;

		result.GetActor()->TakeDamage(m_Attack,DmgEvent,m_Owner->GetController(),m_Owner);
	}
}