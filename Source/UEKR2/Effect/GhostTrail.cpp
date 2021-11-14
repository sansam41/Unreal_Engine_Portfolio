// Fill out your copyright notice in the Description page of Project Settings.


#include "GhostTrail.h"

// Sets default values
AGhostTrail::AGhostTrail()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Mesh= CreateDefaultSubobject<UPoseableMeshComponent>(TEXT("Mesh"));

	SetRootComponent(m_Mesh);

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> GhostMtrlAsset(TEXT("Material'/Game/Materials/MTGhost.MTGhost'"));

	if(GhostMtrlAsset.Succeeded())
		m_GhostMaterial = GhostMtrlAsset.Object;

	m_LifeTime = 1.f;
	m_GhostType = EGhostTrailType::Fade;

	m_FadeTime = 3.f;
	m_FadeTimeAcc = 0.f;
}

// Called when the game starts or when spawned
void AGhostTrail::BeginPlay()
{
	Super::BeginPlay();

	
	//SetLifeSpan(1.f);
}

// Called every frame
void AGhostTrail::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_LifeTime -= DeltaTime;

	if(m_LifeTime <= 0.f)
	{
		switch (m_GhostType)
		{
		case EGhostTrailType::LifeSpan:
			Destroy();
			break;
			
		case EGhostTrailType::Fade:
			{
				m_FadeTimeAcc+=DeltaTime;
				float Opacity = 1.f - m_FadeTimeAcc / m_FadeTime;
				for(auto& Mtrl : m_GhostMaterialArray)
				{
					Mtrl->SetScalarParameterValue(TEXT("Opacity"),Opacity);
				}
				break;
			}
		}
	}

}



void AGhostTrail::SetMesh(const FString& Path)
{
	USkeletalMesh* Mesh = LoadObject<USkeletalMesh>(GetWorld(),*Path);
	
	if(Mesh)
		m_Mesh->SetSkeletalMesh(Mesh);
}
	
void AGhostTrail::SetMesh(USkeletalMesh* Mesh)
{
	m_Mesh->SetSkeletalMesh(Mesh);
	
	int32 MtrlCount = m_Mesh->GetNumMaterials();
	
	for(int32 i = 0;i<MtrlCount;++i)
	{
		UMaterialInstanceDynamic* Mtrl = m_Mesh->CreateDynamicMaterialInstance(i,m_GhostMaterial);
		
		m_GhostMaterialArray.Add(Mtrl);
	}
}


void AGhostTrail::CopyAnimation(USkeletalMeshComponent* Com)
{
	m_Mesh->CopyPoseFromSkeletalComponent(Com);
}
