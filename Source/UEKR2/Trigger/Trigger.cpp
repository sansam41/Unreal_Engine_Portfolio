// Fill out your copyright notice in the Description page of Project Settings.


#include "Trigger.h"

// Sets default values
ATrigger::ATrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_Other = nullptr;
}

// Called when the game starts or when spawned
void ATrigger::BeginPlay()
{
	Super::BeginPlay();

	m_Trigger->OnComponentBeginOverlap.AddDynamic(this,&ATrigger::TriggerBeginOverlap);
	m_Trigger->OnComponentEndOverlap.AddDynamic(this,&ATrigger::TriggerEndOverlap);
}

// Called every frame
void ATrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ATrigger::TriggerBeginOverlap(UPrimitiveComponent* OverlapCom, AActor* OtherActor,
	UPrimitiveComponent* OtherCom,int32 OtherBodyIndex,bool bFromSweep,
	const FHitResult& SweepResult)
{
	m_Other = OtherActor;
	PrintViewport(1.f,FColor::Red,TEXT("Begin Trigger"));
	m_TriggerBeginDelegate.Broadcast();
}

void ATrigger::TriggerEndOverlap(UPrimitiveComponent* OverlapCom, AActor* OtherActor,
	UPrimitiveComponent* OtherCom,int32 OtherBodyIndex)
{
	PrintViewport(1.f,FColor::Red,TEXT("End Trigger"));
	m_TriggerEndDelegate.Broadcast();

	m_Other = nullptr;
}
