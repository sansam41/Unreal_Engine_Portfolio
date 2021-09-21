// Fill out your copyright notice in the Description page of Project Settings.


#include "GreystoneSkill2.h"
#include "NormalEffect.h"
#include "GreystoneSkill2Decal.h"

AGreystoneSkill2::AGreystoneSkill2() {
	PrimaryActorTick.bCanEverTick = true;

	m_Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	m_Particle->SetupAttachment(m_Body);
	m_Damage=75.f;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> Asset(TEXT("ParticleSystem'/Game/AdvancedMagicFX13/Particles/P_ky_stabShot.P_ky_stabShot'"));
	if (Asset.Succeeded())
		m_Particle->SetTemplate(Asset.Object);
}
// Called when the game starts or when spawned
void AGreystoneSkill2::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGreystoneSkill2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



void AGreystoneSkill2::StopEvent(const FHitResult& result)
{
	Super::StopEvent(result);

	FActorSpawnParameters	param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(),
		result.ImpactPoint, result.ImpactNormal.Rotation(), param);

	Effect->LoadParticle(TEXT("ParticleSystem'/Game/AdvancedMagicFX13/Particles/P_ky_hit_slash.P_ky_hit_slash'"));

	Effect->LoadSound(TEXT("SoundWave'/Game/Sound/Fire2.Fire2'"));

	m_Particle->DestroyComponent();


	FCollisionQueryParams params(NAME_None, false, this);
	FHitResult LineResult;
	bool Collision = GetWorld()->LineTraceSingleByChannel(LineResult, GetActorLocation(),
		GetActorLocation() + GetActorUpVector() * -300.0f,
		ECollisionChannel::ECC_GameTraceChannel5,
		params);

	if(IsValid(this))
	{
		FDamageEvent	DmgEvent;
	
		result.GetActor()->TakeDamage(m_Damage,DmgEvent,this->GetInstigatorController(),this);
	}
	
	if (Collision) {
		FActorSpawnParameters param1;
		param1.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AGreystoneSkill2Decal* Decal = GetWorld()->SpawnActor<AGreystoneSkill2Decal>(AGreystoneSkill2Decal::StaticClass(),
			LineResult.ImpactPoint, FRotator::ZeroRotator, param1);
	}
}
