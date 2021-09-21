// Fill out your copyright notice in the Description page of Project Settings.


#include "Kallari.h"


AKallari::AKallari()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	KallariAsset(TEXT("SkeletalMesh'/Game/ParagonKallari/Characters/Heroes/Kallari/Skins/RedDeath/Meshes/Kallari_RedDeath.Kallari_RedDeath'"));

	// GetMesh(): Character클래스에 만들어져있는 SkeletalMeshComponent를 얻어오는 함수이다.
	if (KallariAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(KallariAsset.Object);



	static ConstructorHelpers::FClassFinder<UAnimInstance>	KallariAnimAsset(TEXT("AnimBlueprint'/Game/Player/BPKallariAnim.BPKallariAnim_C'"));


	if (KallariAnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(KallariAnimAsset.Class);


}




// 게임이 시작될 때나 스폰될 때 호출되는 함수
void AKallari::BeginPlay()
{
	Super::BeginPlay();



}

// 매 프레임마다 호출
void AKallari::Tick(float DeltaTime)
{
	// super: 부모클래스를 의미한다.
	Super::Tick(DeltaTime);

}

// 입력처리 때 호출
void AKallari::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}