// Fill out your copyright notice in the Description page of Project Settings.


#include "TestCharacter.h"

// Sets default values
ATestCharacter::ATestCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	PlayerBody(TEXT("SkeletalMesh'/Game/ModularRPGHeroesPolyart/Meshes/ModularBodyParts/Cloth01SK.Cloth01SK'"));
	
	if (PlayerBody.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(PlayerBody.Object);
	}

	m_PlayerFoot = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Foot"));
	m_PlayerFoot->SetupAttachment(GetMesh());
	m_PlayerFoot->SetMasterPoseComponent(GetMesh());
	
	m_PlayerHead = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Head"));
	m_PlayerHead->SetupAttachment(GetMesh());
	m_PlayerHead->SetMasterPoseComponent(GetMesh());
	
	m_PlayerHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hand"));
	m_PlayerHand->SetupAttachment(GetMesh());
	m_PlayerHand->SetMasterPoseComponent(GetMesh());
	
	m_Shoulder = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Shoulder"));
	m_Shoulder->SetupAttachment(GetMesh());
	m_Shoulder->SetMasterPoseComponent(GetMesh());
	
	m_Crown = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Crown"));
	m_Crown->SetupAttachment(GetMesh());
	m_Crown->SetMasterPoseComponent(GetMesh());
	
	m_Belt = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Belt"));
	m_Belt->SetupAttachment(GetMesh());
	m_Belt->SetMasterPoseComponent(GetMesh());
	
	m_Hair = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hair"));
	m_Hair->SetupAttachment(GetMesh());
	m_Hair->SetMasterPoseComponent(GetMesh());
}

// Called when the game starts or when spawned
void ATestCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

