// Fill out your copyright notice in the Description page of Project Settings.


#include "WraithSkill1Bullet.h"
#include "NormalEffect.h"
#include "UEKR2/Player/PlayerCharacter.h"


// Sets default values
AWraithSkill1Bullet::AWraithSkill1Bullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("ParticleSystem'/Game/AdvancedMagicFX12/particles/P_ky_shot_water.P_ky_shot_water'"));
	if(ParticleAsset.Succeeded())
		m_Particle->SetTemplate(ParticleAsset.Object);
	
	m_Movement->InitialSpeed=2000.f;

	
	m_Body->SetCollisionProfileName(TEXT("PlayerAttack"));
	m_Particle->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
}

// Called when the game starts or when spawned
void AWraithSkill1Bullet::BeginPlay()
{
	Super::BeginPlay();
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if(IsValid(m_Owner))
		PrintViewport(1.f,FColor::Red,TEXT("check"));
	
	Bullet1 = GetWorld()->SpawnActor<AOrbitBullet>(
		AOrbitBullet::StaticClass(),GetActorLocation(),FRotator(0.f,0.f,0.f),param);
	Bullet1->SetAttach(this);
	Bullet1->SetRadian(0);
	Bullet1->SetAttack(50.f);

	
	Bullet2 = GetWorld()->SpawnActor<AOrbitBullet>(
		AOrbitBullet::StaticClass(),GetActorLocation(),FRotator(0.f,0.f,0.f),param);
	Bullet2->SetAttach(this);
	Bullet2->SetRadian(2*PI*0.3333f);
	Bullet2->SetAttack(50.f);
	
	Bullet3 = GetWorld()->SpawnActor<AOrbitBullet>(
		AOrbitBullet::StaticClass(),GetActorLocation(),FRotator(0.f,0.f,0.f),param);
	Bullet3->SetAttach(this);
	Bullet3->SetRadian(2*PI*0.6666f);
	Bullet3->SetAttack(50.f);
}

// Called every frame
void AWraithSkill1Bullet::Tick(float DeltaTime)
{
	//Super::Tick(DeltaTime);
	m_DestroyTime += DeltaTime;

	if (m_DestroyTimeMax <= m_DestroyTime)
	{
		this->Bullet1->Destroy();
		this->Bullet2->Destroy();
		this->Bullet3->Destroy();
		Destroy();
	}
}


void AWraithSkill1Bullet::StopEvent(const FHitResult& result)
{
	Super::StopEvent(result);

	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(),
		result.ImpactPoint,result.ImpactNormal.Rotation(),param);

	Effect->LoadParticle(TEXT("ParticleSystem'/Game/AdvancedMagicFX12/particles/P_ky_hit_water.P_ky_hit_water'"));

	// Sound
	Effect->LoadSound(TEXT("SoundWave'/Game/Sound/WaterBomb_Cut.WaterBomb_Cut'"));
	
	m_Particle->DestroyComponent();

	if(IsValid(m_Owner))
	{
		FDamageEvent	DmgEvent;

		PrintViewport(1.f,FColor::Red,TEXT("SKillin"));
		result.GetActor()->TakeDamage(m_Attack,DmgEvent,m_Owner->GetController(),m_Owner);
	}
	this->Bullet1->Destroy();
	this->Bullet2->Destroy();
	this->Bullet3->Destroy();
	this->Destroy();
}
