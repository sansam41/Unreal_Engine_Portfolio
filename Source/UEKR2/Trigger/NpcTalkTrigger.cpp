// Fill out your copyright notice in the Description page of Project Settings.


#include "NpcTalkTrigger.h"


ANpcTalkTrigger::ANpcTalkTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ANpcTalkTrigger::BeginPlay()
{
	Super::BeginPlay();

	m_TriggerBeginDelegate.AddDynamic(this,&ANpcTalkTrigger::TriggerBegin);
	m_TriggerEndDelegate.AddDynamic(this,&ANpcTalkTrigger::TriggerEnd);


}

// Called every frame
void ANpcTalkTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void ANpcTalkTrigger::TriggerBegin()
{
}

void ANpcTalkTrigger::TriggerEnd()
{
	
}
