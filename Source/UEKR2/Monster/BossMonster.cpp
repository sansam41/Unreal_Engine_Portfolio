// Fill out your copyright notice in the Description page of Project Settings.


#include "BossMonster.h"

// Sets default values
ABossMonster::ABossMonster()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//AIControllerClass = AMinionAIController::StaticClass();

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/ParagonSevarog/Characters/Heroes/Sevarog/Skins/Tier_1/Sevarog_Chronos/Meshes/SevarogChronos.SevarogChronos'"));

	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
/*
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("AnimBlueprint'/Game/Monster/BPMinionGunnerAnim.BPMinionGunnerAnim_C'"));
	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);
*/
	m_MonsterInfoName = TEXT("Sevarog");
}

// Called when the game starts or when spawned
void ABossMonster::BeginPlay()
{
	GetMesh()->CreateDynamicMaterialInstance(0);
	Super::BeginPlay();

}

// Called every frame
void ABossMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
