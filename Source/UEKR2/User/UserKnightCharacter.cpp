// Fill out your copyright notice in the Description page of Project Settings.


#include "UserKnightCharacter.h"


// Sets default values
AUserKnightCharacter::AUserKnightCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	GreystoneAsset(TEXT("SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Skins/WhiteTiger/Meshes/Greystone_WhiteTiger.Greystone_WhiteTiger'"));

	// GetMesh() : Character클래스에 만들어져있는 SkeletalMeshComponent를 얻어오는 함수이다.
	if (GreystoneAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(GreystoneAsset.Object);
	}


	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));

	GetMesh()->SetReceivesDecals(false);
	SetCanBeDamaged(true);
}

// Called when the game starts or when spawned
void AUserKnightCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AUserKnightCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
