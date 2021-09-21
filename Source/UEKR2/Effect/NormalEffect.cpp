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
		// 델리게이트로 존재(함수포인터를 가지고있고 호출될 때 함수를 호출)
		// OnSystemFinished : 이 파티클시스템컴포넌트가 가지고 있는 파티클 시스템이 재생이
		// 모두 종료가 되었을 경우 호출될 함수를 지정해둔다.
		// 종료시 지정된 함수가 호출된다.
		m_ParticleSystem->OnSystemFinished.AddDynamic(this, &ANormalEffect::ParticleFinish);
	}
}

// Called every frame
void ANormalEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANormalEffect::LoadParticle(const FString& Path) {
	// 실시간으로 객체 생성
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

