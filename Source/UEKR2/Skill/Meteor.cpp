// Fill out your copyright notice in the Description page of Project Settings.


#include "Meteor.h"

#include "UEKR2/Effect/NormalEffect.h"
#include "UEKR2/Effect/ParticleProjectile.h"

// Sets default values
AMeteor::AMeteor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//m_Root=CreateDefaultSubobject<USphereComponent>(TEXT("Root"));
	m_Body=CreateDefaultSubobject<USphereComponent>(TEXT("Body"));
	m_Mesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	m_Particle=CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	m_Movement=CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));

	SetRootComponent(m_Body);

	
	//m_Body->SetupAttachment(m_Root);
	m_Body->SetSphereRadius(130.f);

	m_Body->SetCollisionProfileName(TEXT("PlayerAttack"));

	m_Mesh->SetupAttachment(m_Body);
	m_Mesh->SetRelativeLocation(FVector(0.f,0.f,-20.f));
	m_Mesh->SetRelativeRotation(FRotator(0.f,0.f,90.f));
	m_Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	m_Particle->SetupAttachment(m_Mesh);
	m_Particle->SetRelativeLocation(FVector(0.f,80.f,70.f));
	m_Particle->SetRelativeScale3D(FVector(3.f,2.f,2.f));
	
	m_Movement->Velocity =FVector(0.f,0.f,-1.f);
	m_Movement->InitialSpeed=1000.f;

	m_Damage=175.f;

	//m_Movement->SetUpdatedComponent(m_Root);
	

	
	static ConstructorHelpers::FObjectFinder<UStaticMesh>	MeshAsset(TEXT("StaticMesh'/Game/Light_Foliage/Meshes/SM_Rock_02.SM_Rock_02'"));

	if(MeshAsset.Succeeded())
		m_Mesh->SetStaticMesh(MeshAsset.Object);

	
	static ConstructorHelpers::FObjectFinder<UParticleSystem>	ParticleAsset(TEXT("ParticleSystem'/Game/AdvancedMagicFX12/particles/P_ky_shot_fire.P_ky_shot_fire'"));

	if(ParticleAsset.Succeeded())
		m_Particle->SetTemplate(ParticleAsset.Object);


}

// Called when the game starts or when spawned
void AMeteor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMeteor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	m_Movement->OnProjectileStop.AddDynamic(this,&AMeteor::ProjectileStop);
}


void AMeteor::ProjectileStop(const FHitResult& result)
{
	StopEvent(result);
}

void AMeteor::StopEvent(const FHitResult& result)
{

	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(),
		result.ImpactPoint,result.ImpactNormal.Rotation(),param);

	Effect->LoadParticle(TEXT("ParticleSystem'/Game/AdvancedMagicFX13/Particles/P_ky_explosion3.P_ky_explosion3'"));

	// Sound
	Effect->LoadSound(TEXT("SoundWave'/Game/Sound/Fire4.Fire4'"));


	if(IsValid(this))
	{
		FDamageEvent	DmgEvent;
	
		result.GetActor()->TakeDamage(m_Damage,DmgEvent,this->GetInstigatorController(),this);
	}

	this->Destroy();

}
