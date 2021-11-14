// Fill out your copyright notice in the Description page of Project Settings.


#include "WraithBullet.h"
#include "NormalEffect.h"
#include "UEKR2/Player/PlayerCharacter.h"

// Sets default values
AWraithBullet::AWraithBullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("ParticleSystem'/Game/AdvancedMagicFX13/Particles/P_ky_stabShot.P_ky_stabShot'"));

	if(ParticleAsset.Succeeded())
		m_Particle->SetTemplate(ParticleAsset.Object);

	m_Movement->InitialSpeed=2000.f;

	
	//m_Body->SetCollisionProfileName(TEXT("EnemyAttack"));
	m_Body->SetCollisionProfileName(TEXT("PlayerAttack"));
	
	
}

// Called when the game starts or when spawned
void AWraithBullet::BeginPlay()
{
	Super::BeginPlay();
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
}

// Called every frame
void AWraithBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AWraithBullet::StopEvent(const FHitResult& result)
{
	Super::StopEvent(result);

	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(),
		result.ImpactPoint,result.ImpactNormal.Rotation(),param);

	Effect->LoadParticle(TEXT("ParticleSystem'/Game/AdvancedMagicFX13/Particles/P_ky_flash1.P_ky_flash1'"));

	// Sound
	Effect->LoadSound(TEXT("SoundWave'/Game/Sound/Gun12.Gun12'"));
	
	m_Particle->DestroyComponent();

	if(IsValid(m_Owner))
	{
		FDamageEvent	DmgEvent;

		result.GetActor()->TakeDamage(m_Attack,DmgEvent,m_Owner->GetController(),m_Owner);
	}
	this->Destroy();
}
