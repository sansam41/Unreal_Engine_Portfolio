// Fill out your copyright notice in the Description page of Project Settings.


#include "FireTrap.h"


// Sets default values
AFireTrap::AFireTrap()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	m_Body=CreateDefaultSubobject<USphereComponent>(TEXT("Body"));
	m_Mesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	m_Particle=CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	m_Movement=CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));

	SetRootComponent(m_Body);
	m_Body->SetSphereRadius(130.f);
	m_Body->SetRelativeRotation(FRotator(0.f,0.f,0.f));
	m_Body->SetCollisionProfileName(TEXT("EnemyAttack"));

	m_Mesh->SetupAttachment(m_Body);
	m_Mesh->SetRelativeLocation(FVector(0.f,0.f,-70.f));
	
	m_Particle->SetupAttachment(m_Mesh);
	m_Particle->SetRelativeLocation(FVector(0.f,0.f,0.f));
	m_Particle->SetRelativeScale3D(FVector(1.f,1.f,1.f));
	
	//m_Movement->Velocity =FVector(0.f,0.f,-1.f);
	//m_Movement->InitialSpeed=100.f;
	

	
	//static ConstructorHelpers::FObjectFinder<UStaticMesh>	MeshAsset(TEXT("StaticMesh'/Game/Light_Foliage/Meshes/SM_Rock_02.SM_Rock_02'"));
	//
	//if(MeshAsset.Succeeded())
	//	m_Mesh->SetStaticMesh(MeshAsset.Object);

	
	static ConstructorHelpers::FObjectFinder<UParticleSystem>	ParticleAsset(TEXT("ParticleSystem'/Game/AdvancedMagicFX13/Particles/P_ky_fireStorm.P_ky_fireStorm'"));

	if(ParticleAsset.Succeeded())
		m_Particle->SetTemplate(ParticleAsset.Object);
}

// Called when the game starts or when spawned
void AFireTrap::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AFireTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_DestroyTime += DeltaTime;

	if (2.5f <= m_DestroyTime)
		Destroy();
}

