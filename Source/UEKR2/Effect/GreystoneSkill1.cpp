// Fill out your copyright notice in the Description page of Project Settings.


#include "GreystoneSkill1.h"
#include "NormalEffect.h"
#include "GreystoneSkill1Decal.h"

// Sets default values
AGreystoneSkill1::AGreystoneSkill1()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	m_Particle->SetupAttachment(m_Body);
	m_Damage=100.f;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> Asset(TEXT("ParticleSystem'/Game/AdvancedMagicFX13/Particles/P_ky_cutter2.P_ky_cutter2'"));
	if (Asset.Succeeded())
		m_Particle->SetTemplate(Asset.Object);
}

// Called when the game starts or when spawned
void AGreystoneSkill1::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AGreystoneSkill1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!m_DestroyEnable)
		m_Mesh->AddRelativeRotation(FRotator(0.f, 1080.f * DeltaTime, 0.f));
}

void AGreystoneSkill1::StopEvent(const FHitResult& result)
{
	Super::StopEvent(result);

	FActorSpawnParameters	param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(),
		result.ImpactPoint, result.ImpactNormal.Rotation(), param);

	// 애셋을 로딩한다.
	Effect->LoadParticle(TEXT("ParticleSystem'/Game/AdvancedMagicFX13/Particles/P_ky_explosion3.P_ky_explosion3'"));

	// Sound
	Effect->LoadSound(TEXT("SoundWave'/Game/Sound/Fire4.Fire4'"));

	m_Particle->DestroyComponent();

	// 현재 위치에서 아래로 레이 체크를 한다.
	
	FCollisionQueryParams	params(NAME_None, false, this);
	FHitResult LineResult;
	bool Collision = GetWorld()->LineTraceSingleByChannel(LineResult, GetActorLocation(),
		GetActorLocation() + GetActorUpVector() * -300.f,
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
		AGreystoneSkill1Decal* Decal = GetWorld()->SpawnActor<AGreystoneSkill1Decal>(AGreystoneSkill1Decal::StaticClass(),
			LineResult.ImpactPoint, FRotator::ZeroRotator, param1);
	}
}

