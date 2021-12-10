// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestNpc.h"

AQuestNpc::AQuestNpc()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/ModularRPGHeroesPolyart/Meshes/OneMeshCharacters/CommonerSK.CommonerSK'"));
	m_NpcInfo.Name = "Quest_NPC";
	m_NpcInfo.Dialogue.Push(TEXT("밖에 돌아다니는 상자괴물을 처리해줘!"));
	m_NpcInfo.Dialogue.Push(TEXT("숲을 빠져나가면 있는 도적 쥐를 처리해줘!"));
	m_NpcInfo.Dialogue.Push(TEXT("성을 점거한 흑기사를 처리해줘!"));
	m_NpcInfo.Dialogue.Push(TEXT("네번째 퀘스트."));
	m_NpcInfo.Dialogue2.Push(TEXT("빨리하고와!"));
	m_NpcInfo.Dialogue2.Push(TEXT("잘했어! 보상을 주지"));
	m_NpcInfo.Type = 1;
	m_QuestProgress = 0;
	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

}

// Called when the game starts or when spawned
void AQuestNpc::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AQuestNpc::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
