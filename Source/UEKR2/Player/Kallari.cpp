// Fill out your copyright notice in the Description page of Project Settings.


#include "Kallari.h"


AKallari::AKallari()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	KallariAsset(TEXT("SkeletalMesh'/Game/ParagonKallari/Characters/Heroes/Kallari/Skins/RedDeath/Meshes/Kallari_RedDeath.Kallari_RedDeath'"));

	// GetMesh(): CharacterŬ������ ��������ִ� SkeletalMeshComponent�� ������ �Լ��̴�.
	if (KallariAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(KallariAsset.Object);



	static ConstructorHelpers::FClassFinder<UAnimInstance>	KallariAnimAsset(TEXT("AnimBlueprint'/Game/Player/BPKallariAnim.BPKallariAnim_C'"));


	if (KallariAnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(KallariAnimAsset.Class);


}




// ������ ���۵� ���� ������ �� ȣ��Ǵ� �Լ�
void AKallari::BeginPlay()
{
	Super::BeginPlay();



}

// �� �����Ӹ��� ȣ��
void AKallari::Tick(float DeltaTime)
{
	// super: �θ�Ŭ������ �ǹ��Ѵ�.
	Super::Tick(DeltaTime);

}

// �Է�ó�� �� ȣ��
void AKallari::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}