// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "RPG_PlayerCharacter.h"
#include "RPG_Knight.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API ARPG_Knight : public ARPG_PlayerCharacter
{
	GENERATED_BODY()
	
	public:
	// Sets default values for this character's properties
	ARPG_Knight();

	protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage*> m_AttackMontageArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage*> m_SkillMontageArray;

	// UClassÁ¤º¸¸¦ °¡Áü
	//TSubclassOf<AGreystoneSkill1> m_Skill1Class;

	
	int32 m_AttackIndex;

	
	class AWeapon* m_Weapon;
	class AWeapon* m_Shield;

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
	virtual void UseSkill(int32 Index);

};
