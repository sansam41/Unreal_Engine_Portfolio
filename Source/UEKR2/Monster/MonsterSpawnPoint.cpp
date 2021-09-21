// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSpawnPoint.h"

// Sets default values
AMonsterSpawnPoint::AMonsterSpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_Monster = nullptr;

	m_SpawnTime = 1.f;
	m_AccTime = 0.f;
}

// Called when the game starts or when spawned
void AMonsterSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	

	if (m_MonsterClass) {
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		AMonster* Monster = GetWorld()->SpawnActor<AMonster>(m_MonsterClass, GetActorLocation(), GetActorRotation(), param);

		Monster->SetSpawnPoint(this);

		Monster->AddPatrolPoint(GetActorLocation());

		for(auto& Point : m_PatrolPointArray)
		{
			Monster->AddPatrolPoint(Point->GetActorLocation());
		}
		
		
		m_Monster = Monster;

		
	}
}

// Called every frame
void AMonsterSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!m_Monster) {
		m_AccTime += DeltaTime;
		if (m_AccTime >= m_SpawnTime) {
			m_AccTime = 0.f;
			FActorSpawnParameters param;
			param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			if (m_MonsterClass) {
				AMonster* Monster = GetWorld()->SpawnActor<AMonster>(m_MonsterClass, GetActorLocation(), GetActorRotation(), param);
				m_Monster=Monster;
				Monster->SetSpawnPoint(this);
				Monster->AddPatrolPoint(GetActorLocation());

				for (auto& Point : m_PatrolPointArray)
				{
					Monster->AddPatrolPoint(Point->GetActorLocation());
				}
			}
		}
	}
}

