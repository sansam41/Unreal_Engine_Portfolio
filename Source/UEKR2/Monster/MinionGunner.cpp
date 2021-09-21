// Fill out your copyright notice in the Description page of Project Settings.


#include "MinionGunner.h"
#include "../Effect/MinionGunnerBullet.h"

// Sets default values
AMinionGunner::AMinionGunner()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/ParagonMinions/Characters/Minions/Down_Minions/Meshes/Minion_Lane_Ranged_Dawn.Minion_Lane_Ranged_Dawn'"));

	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("AnimBlueprint'/Game/Monster/BPMinionGunnerAnim.BPMinionGunnerAnim_C'"));
	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);

	m_MonsterInfoName = TEXT("MinionGunner");
}

// Called when the game starts or when spawned
void AMinionGunner::BeginPlay()
{
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

	Bullet->SetAttack(m_MonsterInfo.Attack);
	Bullet->SetOwner(this);
}
