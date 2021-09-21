// Fill out your copyright notice in the Description page of Project Settings.


#include "SphereTrigger.h"


// Sets default values
ASphereTrigger::ASphereTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));
	SetRootComponent(m_Trigger);

	m_ShapeType=ETriggerType::Sphere;
}

// Called when the game starts or when spawned
void ASphereTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASphereTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}