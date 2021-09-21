// Fill out your copyright notice in the Description page of Project Settings.


#include "GreystoneSkill3Decal.h"

// Sets default values
AGreystoneSkill3Decal::AGreystoneSkill3Decal()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UMaterialInstance> DecalMtrlAsset(TEXT("MaterialInstanceConstant'/Game/Player/Greystone/MTGreystoneMagicCircle_Inst.MTGreystoneMagicCircle_Inst'"));
	if (DecalMtrlAsset.Succeeded()) {
		m_Decal->SetDecalMaterial(DecalMtrlAsset.Object);
	}


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

}