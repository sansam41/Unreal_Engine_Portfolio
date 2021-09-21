// Fill out your copyright notice in the Description page of Project Settings.


#include "CapsuleTrigger.h"


// Sets default values
ACapsuleTrigger::ACapsuleTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_Trigger = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger"));
	SetRootComponent(m_Trigger);

	m_ShapeType=ETriggerType::Capsule;
}

// Called when the game starts or when spawned
void ACapsuleTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACapsuleTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}