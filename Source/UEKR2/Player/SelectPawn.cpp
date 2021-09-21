// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectPawn.h"

// Sets default values
ASelectPawn::ASelectPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	m_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	SetRootComponent(m_Camera);

	m_Camera->SetRelativeLocation(FVector(0.f,0.f,100.f));
}

// Called when the game starts or when spawned
void ASelectPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASelectPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASelectPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

