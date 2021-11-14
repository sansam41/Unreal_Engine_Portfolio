// Fill out your copyright notice in the Description page of Project Settings.


#include "GreystoneSkill3Decal.h"

// Sets default values
AGreystoneSkill3Decal::AGreystoneSkill3Decal()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UMaterialInstance> DecalMtrlAsset(TEXT("MaterialInstanceConstant'/Game/Player/Greystone/MTGreystoneMagicCircle_Inst.MTGreystoneMagicCircle_Inst'"));

	if (DecalMtrlAsset.Succeeded())
		m_Decal->SetDecalMaterial(DecalMtrlAsset.Object);


	m_Material = m_Decal->CreateDynamicMaterialInstance();
	m_Glow=5.f;
	m_Dir=1.f;
}

// Called when the game starts or when spawned
void AGreystoneSkill3Decal::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGreystoneSkill3Decal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_Glow+=m_Dir*DeltaTime*5.f;
	if(m_Glow>=10.f)
	{
		m_Glow=10.f;
		m_Dir=-1.f;
	}
	else if(m_Glow<=1.f)
	{
		m_Glow=1.f;
		m_Dir=1.f;
	}

	m_Material->SetScalarParameterValue(TEXT("Glow"),m_Glow);
	//m_Material->SetVectorParameterValue();	// 벡터 변경
	//m_Material->SetTextureParameterValue();	// 텍스처 변경
	
	AddActorWorldRotation(FRotator(0.f,180.f*DeltaTime,0.f));
}