// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/SceneCaptureComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"



UCLASS(config=MainAsset)
class UEKR2_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// ī�޶� ������Ʈ
	// ������ �����ͳ� ��������Ϳ� ������ �ϰ���� ��
	// ������Ƽ �����ڸ� ����Ͽ� ����
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

	bool m_OnGhostTrail;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess="true"))
	float m_GhostTrailTime;
	
	float m_GhostTrailTimeAcc;
	
	USkeletalMesh* m_PlayerMesh;


	bool m_MoveKey;
	bool m_AttackEnable;
	bool m_Death;
	bool m_Attack;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess="true"))
	bool m_Casting;
	bool m_ShowUI;




	class UPlayerAnim* m_AnimInstance;

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
	void GameSaveKey();
	void PlayFallRecovery();

	void changeShowUI();


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


	void GhostTrailEnd();
	void OnGhostTrail();


public:
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	UFUNCTION()
	void NameWidgetCallback();

	UFUNCTION()
	void CharacterNameWidgetCallback();

public:
	void FootStep(bool Left);
};
