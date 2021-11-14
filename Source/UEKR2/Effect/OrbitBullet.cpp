// Fill out your copyright notice in the Description page of Project Settings.


#include "OrbitBullet.h"
#include "NormalEffect.h"
#include "OribitBulletMovement.h"

// Sets default values
AOrbitBullet::AOrbitBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	m_Body = CreateDefaultSubobject<UBoxComponent>(TEXT("Body"));
	m_Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Mesh"));
	m_ParticleMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ParticleMovement"));
	m_Movement = CreateDefaultSubobject<UOribitBulletMovement>(TEXT("Movement"));
	
	m_Particle->SetWorldScale3D(FVector(0.3f));
	RootComponent = m_Body;
	m_Particle->SetupAttachment(m_Body);

	m_Movement->m_UpdateComponent = RootComponent;

	m_ParticleMovement->SetUpdatedComponent(m_Body);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("ParticleSystem'/Game/AdvancedMagicFX13/Particles/P_ky_stabShot.P_ky_stabShot'"));

	if(ParticleAsset.Succeeded())
		m_Particle->SetTemplate(ParticleAsset.Object);

	
	m_Body->SetCollisionProfileName(TEXT("PlayerAttack"));
}

// Called when the game starts or when spawned
void AOrbitBullet::BeginPlay()
{
	Super::BeginPlay();
	
	m_ParticleMovement->OnProjectileStop.AddDynamic(this,&AOrbitBullet::ProjectileStop);
}

// Called every frame
void AOrbitBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void AOrbitBullet::SetAttach(AActor* Parent)
{
	AttachToActor(Parent,FAttachmentTransformRules(EAttachmentRule::KeepRelative,true),NAME_None);
}

void AOrbitBullet::SetRadian(float Radian)
{
	m_Movement->m_Radian = Radian;
}


void AOrbitBullet::ProjectileStop(const FHitResult& result)
{
	StopEvent(result);
}

void AOrbitBullet::StopEvent(const FHitResult& result)
{

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
		PrintViewport(1.f,FColor::Red,TEXT("in"));
		result.GetActor()->TakeDamage(m_Attack,DmgEvent,m_Owner->GetController(),m_Owner);
	}
	this->Destroy();
}
