// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "PlayerCharacter.h"
#include "../Effect/GreystoneSkill1.h"
#include "../Effect/GreystoneSkill2.h"
#include "UEKR2/Skill/Meteor.h"
#include "Greystone.generated.h"


UCLASS()
class UEKR2_API AGreystone : public APlayerCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGreystone();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage*> m_AttackMontageArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage*> m_SkillMontageArray;

	UAnimMontage* m_Skill3FireMontage;
	// UClassÁ¤º¸¸¦ °¡Áü
	TSubclassOf<AGreystoneSkill1> m_Skill1Class;

	TSubclassOf<AGreystoneSkill2> m_Skill2Class;
	
	TSubclassOf<AMeteor> m_Skill3Class;

	

	int32 m_AttackIndex;

	class AWeapon* m_Weapon;

	bool m_OnSkill3;


	class AGreystoneSkill3Decal* m_Skill3Decal;

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
	virtual void Skill2();
	virtual void Skill3();

public:
	virtual void NormalAttack();
	virtual void AttackEnd();
	virtual void AttackCombo();
	virtual void UseSkill(int32 Index);
	virtual void UseSkillFire(int32 Index);
	
};