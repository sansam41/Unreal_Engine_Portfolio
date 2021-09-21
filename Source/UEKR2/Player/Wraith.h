// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "PlayerCharacter.h"
#include "Wraith.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API AWraith : public APlayerCharacter
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	AWraith();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage*> m_AttackMontageArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage*> m_SkillMontageArray;

	// UClassÁ¤º¸¸¦ °¡Áü
	//TSubclassOf<AGreystoneSkill1> m_Skill1Class;

	int32 m_AttackIndex;

	//class AWeapon* m_Weapon;
	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	

protected:
	virtual void Attack();
	virtual void Skill1();

public:
	virtual void NormalAttack();
	virtual void AttackEnd();
	virtual void AttackCombo();
	virtual void UseSkill(int32 Index);

};
