// Fill out your copyright notice in the Description page of Project Settings.


#include "GreystoneSkill2Decal.h"

// Sets default values
AGreystoneSkill2Decal::AGreystoneSkill2Decal()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMtrlAsset(TEXT("Material'/Game/Player/Greystone/MTGreystoneSkill2.MTGreystoneSkill2'"));
	if (DecalMtrlAsset.Succeeded()) {
		m_Decal->SetDecalMaterial(DecalMtrlAsset.Object);
	}


}

// Called when the game starts or when spawned
void AGreystoneSkill2Decal::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(5.f);
}

// Called every frame
void AGreystoneSkill2Decal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}