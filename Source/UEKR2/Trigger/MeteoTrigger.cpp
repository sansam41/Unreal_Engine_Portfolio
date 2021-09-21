// Fill out your copyright notice in the Description page of Project Settings.


#include "MeteoTrigger.h"

#include "UEKR2/Skill/Meteor.h"

AMeteoTrigger::AMeteoTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMeteoTrigger::BeginPlay()
{
	Super::BeginPlay();

	m_TriggerBeginDelegate.AddDynamic(this,&AMeteoTrigger::TriggerBegin);
	m_TriggerEndDelegate.AddDynamic(this,&AMeteoTrigger::TriggerEnd);


}

// Called every frame
void AMeteoTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void AMeteoTrigger::TriggerBegin()
{
	FActorSpawnParameters param;

	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AMeteor* Meteor = GetWorld()->SpawnActor<AMeteor>(AMeteor::StaticClass(),
		GetActorLocation()+FVector(0.f,0.f,500.f),
		FRotator::ZeroRotator,param);
}

void AMeteoTrigger::TriggerEnd()
{
	
}
