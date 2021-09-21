// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxTrigger.h"

// Sets default values
ABoxTrigger::ABoxTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	SetRootComponent(m_Trigger);


	//m_Trigger->OnComponentBeginOverlap
	m_ShapeType=ETriggerType::Box;
}

// Called when the game starts or when spawned
void ABoxTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoxTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
