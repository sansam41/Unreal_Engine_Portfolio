// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructibleProjectile.h"

// Sets default values
ADestructibleProjectile::ADestructibleProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Body = CreateDefaultSubobject<UBoxComponent>(TEXT("Body"));
	m_Mesh = CreateDefaultSubobject<UDestructibleComponent>(TEXT("Mesh"));
	m_Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));

	SetRootComponent(m_Body);

	m_Mesh->SetupAttachment(m_Body);

	m_Movement->SetUpdatedComponent(m_Body);

	m_Movement->InitialSpeed = 1000.f;

	m_DestroyEnable = false;
	m_DestroyTime = 0.f;
	m_DestroyTimeMax = 5.f;

	m_Distance = 2000.f;

	m_Mesh->SetReceivesDecals(false);
}

// Called when the game starts or when spawned
void ADestructibleProjectile::BeginPlay()
{
	Super::BeginPlay();

	m_Movement->OnProjectileStop.AddDynamic(this, &ADestructibleProjectile::ProjectileStop);
}

// Called every frame
void ADestructibleProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_Distance -= m_Movement->Velocity.Size() * DeltaTime;

	if (m_Distance <= 0.f)
		Destroy();

	if (m_DestroyEnable)
	{
		m_DestroyTime += DeltaTime;

		if (m_DestroyTimeMax <= m_DestroyTime)
			Destroy();
	}
}

void ADestructibleProjectile::ProjectileStop(const FHitResult& result)
{
	StopEvent(result);
}

void ADestructibleProjectile::StopEvent(const FHitResult& result)
{
	m_Mesh->ApplyDamage(10.f, result.ImpactPoint, result.ImpactNormal, 10.f);

	m_DestroyEnable = true;
}
