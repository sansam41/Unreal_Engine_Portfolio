// Fill out your copyright notice in the Description page of Project Settings.


#include "MinionGunner.h"
#include "../Effect/MinionGunnerBullet.h"
#include "MinionGunnerAIController.h"
#include "UEKR2/Effect/NormalEffect.h"


// Sets default values
AMinionGunner::AMinionGunner()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	AIControllerClass = AMinionGunnerAIController::StaticClass();

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/ParagonMinions/Characters/Minions/Down_Minions/Meshes/Minion_Lane_Ranged_Dawn.Minion_Lane_Ranged_Dawn'"));

	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("AnimBlueprint'/Game/Monster/BPMinionGunnerAnim.BPMinionGunnerAnim_C'"));
	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);

	m_MonsterInfoName = TEXT("MinionGunner");

	m_DropItemNameArray.Add(TEXT("칠흑의양날도끼"));
	m_DropItemNameArray.Add(TEXT("MP포션"));
}

// Called when the game starts or when spawned
void AMinionGunner::BeginPlay()
{
	
	GetMesh()->CreateDynamicMaterialInstance(0);
	Super::BeginPlay();
}

// Called every frame
void AMinionGunner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMinionGunner::NormalAttack()
{
	FVector MuzzleLoc=GetMesh()->GetSocketLocation(TEXT("Muzzle_Front"));
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AMinionGunnerBullet* Bullet = GetWorld()->SpawnActor<AMinionGunnerBullet>(
		AMinionGunnerBullet::StaticClass(),MuzzleLoc,GetActorRotation(),param);
	

	ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(),
	MuzzleLoc,GetActorRotation(),param);


	Effect->LoadSound(TEXT("SoundWave'/Game/Sound/ThickLaser.ThickLaser'"));
	Bullet->SetAttack(m_MonsterInfo.Attack);
	Bullet->SetOwner(this);
}
