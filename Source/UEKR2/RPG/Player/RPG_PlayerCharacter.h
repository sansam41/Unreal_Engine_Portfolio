// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Components/SceneCaptureComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "RPG_PlayerCharacter.generated.h"


UCLASS(config=MainAsset)
class UEKR2_API ARPG_PlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARPG_PlayerCharacter();

protected:
	// 카메라 컴포넌트
	// 변수를 에디터나 블루프린터에 노출을 하고싶을 때
	// 프로퍼티 지정자를 사용하여 설정
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess="true"))
	UCameraComponent* m_Camera;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess="true"))
	USpringArmComponent* m_Arm;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess="true"))
	UWidgetComponent* m_HPBar;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess="true"))
	USceneCaptureComponent2D* m_Capture;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess="true"))
	UParticleSystemComponent* m_Trail;

	UAnimMontage* m_FallRecoveryMontage;

	class UHPBar* m_HPBarWidget;

	class UTextureRenderTarget2D* m_FaceTarget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FPlayerInfo m_PlayerInfo;
	
	USkeletalMesh* m_PlayerMesh;


	bool m_MoveKey;
	bool m_AttackEnable;
	bool m_Death;
	bool m_Attack;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess="true"))
	bool m_Casting;
	bool m_ShowUI;




	class URPGPlayerAnim* m_AnimInstance;

	FTimerHandle m_MonsterDetectTimer;

	

public:
	UPROPERTY(Config)
	FString TestString;
public:
	const FPlayerInfo& GetPlayerInfo() const {
		return m_PlayerInfo;
	}
	bool IsMoveKey() const {
		return m_MoveKey;
	}

	void EnableAttack(bool Enable) {
		m_AttackEnable = Enable;
	}

	void SetCasting(bool Cast)
	{

		m_Casting=Cast;

	}
	bool GetShowUI()
	{
		return m_ShowUI;
	}

	FVector GetCameraLocation() const
	{
		return m_Camera->GetComponentLocation();
	}
	
	
	

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	

public:
	void MoveFrontKey(float Scale);
	void MoveSideKey(float Scale);
	void CameraZoomKey(float Scale);
	void CameraLookUpKey(float Scale);
	void CameraRotationKey(float Scale);
	void RotationZKey(float Scale);

	void JumpKey();
	void AttackKey();
	void Skill1Key();
	void Skill2Key();
	void Skill3Key();
	void changeShowUI();


protected:
	virtual void Attack();
	virtual void Skill1();
	virtual void Skill2();
	virtual void Skill3();

public:
	virtual void NormalAttack();
	virtual void AttackEnd();
	virtual void UseSkill(int32 Index);
	virtual void UseSkillFire(int32 Index);
	


public:
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	UFUNCTION()
	void NameWidgetCallback();

	UFUNCTION()
	void CharacterNameWidgetCallback();

public:
	void FootStep(bool Left);

	UFUNCTION()
	void MonsterDetect();
};
