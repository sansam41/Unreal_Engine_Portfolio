// Fill out your copyright notice in the Description page of Project Settings.


#include "GreystoneSkill1Decal.h"

// Sets default values
AGreystoneSkill1Decal::AGreystoneSkill1Decal()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMtrlAsset(TEXT("Material'/Game/Player/Greystone/MTGreystoneSkill1.MTGreystoneSkill1'"));
	if (DecalMtrlAsset.Succeeded()) {
		m_Decal->SetDecalMaterial(DecalMtrlAsset.Object);
	}


}

// Called when the game starts or when spawned
void AGreystoneSkill1Decal::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(5.f);
}

// Called every frame
void AGreystoneSkill1Decal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}