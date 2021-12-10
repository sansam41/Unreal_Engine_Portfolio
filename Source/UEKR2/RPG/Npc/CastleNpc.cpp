// Fill out your copyright notice in the Description page of Project Settings.


#include "CastleNpc.h"

ACastleNpc::ACastleNpc()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	m_NpcInfo.Name = "Castle_NPC";
	m_NpcInfo.Dialogue.Push(TEXT("열쇠가 없으면 들어갈수 없습니다."));
	m_NpcInfo.Dialogue.Push(TEXT("열쇠가 있습니까?"));
	m_NpcInfo.Dialogue2.Push(TEXT("들어갈 수 없습니다."));
	m_NpcInfo.Dialogue2.Push(TEXT("들어가십시오"));
	m_NpcInfo.Type = 2;
	m_key = false;
	m_checked = false;
	m_DialogueProgress = 0;
}

// Called when the game starts or when spawned
void ACastleNpc::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACastleNpc::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACastleNpc::MovePlayer()
{
	Player->SetActorLocation(FVector(2520.0f,-1080.0f,100.0f));
}