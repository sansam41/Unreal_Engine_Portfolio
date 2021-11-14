// Fill out your copyright notice in the Description page of Project Settings.


#include "OribitBulletMovement.h"

// Sets default values for this component's properties
UOribitBulletMovement::UOribitBulletMovement()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	m_Radian = 0.0f;
	m_RevolutionRadius = 100.0f;
}


// Called when the game starts
void UOribitBulletMovement::BeginPlay()
{
	Super::BeginPlay();

	
}


// Called every frame
void UOribitBulletMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	m_Radian += DeltaTime*5.f;

	if(m_Radian > 2 * PI)
		m_Radian -= 2 * PI;

	FVector newLocation = FVector(0.0f,
		FMath::Sin(m_Radian) * m_RevolutionRadius,
		FMath::Cos(m_Radian) * m_RevolutionRadius);

	m_UpdateComponent->SetRelativeLocation(newLocation);
}

