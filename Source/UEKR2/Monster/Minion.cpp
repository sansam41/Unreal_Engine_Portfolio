// Fill out your copyright notice in the Description page of Project Settings.


#include "Minion.h"
#include "MinionAIController.h"

// Sets default values
AMinion::AMinion()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetReceivesDecals(false);
	AIControllerClass = AMinionAIController::StaticClass();

	GetCharacterMovement()->MaxWalkSpeed = 400.f;
}

// Called when the game starts or when spawned
void AMinion::BeginPlay()
{
	Super::BeginPlay();



}

// Called every frame
void AMinion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
