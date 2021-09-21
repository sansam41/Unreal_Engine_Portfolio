// Fill out your copyright notice in the Description page of Project Settings.


#include "NormalEffect.h"

// Sets default values
ANormalEffect::ANormalEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	SetRootComponent(m_ParticleSystem);

	m_AssetLoop = false;
}

// Called when the game starts or when spawned
void ANormalEffect::BeginPlay()
{
	Super::BeginPlay();
	if (!m_AssetLoop) {
		// ��������Ʈ�� ����(�Լ������͸� �������ְ� ȣ��� �� �Լ��� ȣ��)
		// OnSystemFinished : �� ��ƼŬ�ý���������Ʈ�� ������ �ִ� ��ƼŬ �ý����� �����
		// ��� ���ᰡ �Ǿ��� ��� ȣ��� �Լ��� �����صд�.
		// ����� ������ �Լ��� ȣ��ȴ�.
		m_ParticleSystem->OnSystemFinished.AddDynamic(this, &ANormalEffect::ParticleFinish);
	}
}

// Called every frame
void ANormalEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANormalEffect::LoadParticle(const FString& Path) {
	// �ǽð����� ��ü ����
	UParticleSystem* Particle=LoadObject<UParticleSystem>(GetWorld(), *Path);

	if (Particle)
		m_ParticleSystem->SetTemplate(Particle);
}

void ANormalEffect::LoadSound(const FString& Path) {
	USoundBase* Sound = LoadObject<USoundBase>(nullptr, *Path);

	if (Sound)
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, GetActorLocation());
}

void ANormalEffect::ParticleFinish(UParticleSystemComponent* Particle) {
	Destroy();
}

