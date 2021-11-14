// Fill out your copyright notice in the Description page of Project Settings.


#include "EnvironmentNormalActor.h"

// Sets default values
AEnvironmentNormalActor::AEnvironmentNormalActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_Body = CreateDefaultSubobject<UBoxComponent>(TEXT("Body"));
	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	SetRootComponent(m_Body);

	m_Mesh->SetupAttachment(m_Body);

	m_Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	m_Mesh->SetCollisionProfileName(TEXT("Wall"));
	m_DepthSilhouette = false;
	m_CameraCollision = false;


}

// Called when the game starts or when spawned
void AEnvironmentNormalActor::BeginPlay()
{
	Super::BeginPlay();

	if(m_DepthSilhouette)
	{
		m_DynamicMaterial = m_Mesh->CreateDynamicMaterialInstance(0);
	}
}

// Called every frame
void AEnvironmentNormalActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

