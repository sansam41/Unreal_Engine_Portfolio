// Fill out your copyright notice in the Description page of Project Settings.


#include "FireTrapTrigger.h"

#include "UEKR2/Trap/FireTrap.h"

AFireTrapTrigger::AFireTrapTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFireTrapTrigger::BeginPlay()
{
	Super::BeginPlay();

	m_TriggerBeginDelegate.AddDynamic(this,&AFireTrapTrigger::TriggerBegin);
	m_TriggerEndDelegate.AddDynamic(this,&AFireTrapTrigger::TriggerEnd);


}

// Called every frame
void AFireTrapTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



void AFireTrapTrigger::TriggerBegin()
{
	FActorSpawnParameters param;

	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AFireTrap* Meteor = GetWorld()->SpawnActor<AFireTrap>(AFireTrap::StaticClass(),
		GetActorLocation()+FVector(0.f,0.f,-100.f),
		FRotator::ZeroRotator,param);
}

void AFireTrapTrigger::TriggerEnd()
{
	
}
