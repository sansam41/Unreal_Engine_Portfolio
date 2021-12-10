// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/WidgetComponent.h"
#include "MonsterAnimInstance.h"
#include "GameFramework/Character.h"
#include "Monster.generated.h"

USTRUCT(BlueprintType)
struct FMonsterInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString			Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32			Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32			Armor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32			HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32			HPMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32			MP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32			MPMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32			Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32			Exp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32			Gold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float			AttackDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float			AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float			AttackAngle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float			MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float			TraceDistance;
};

UCLASS()
class UEKR2_API AMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonster();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FMonsterInfo	m_MonsterInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* m_HPBar;

	class UHPBar* m_HPBarWidget;

	class AMonsterSpawnPoint* m_SpawnPoint;

	FString			m_MonsterInfoName;

	class UMonsterAnimInstance* m_AnimInstance;

	bool		m_AttackEnd;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<FVector>	m_PatrolArray;
	int32			m_PatrolIndex;

	bool		m_DissolveEnable;
	float		m_Dissolve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		m_DissolveMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		m_DissolveMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		m_DissolveTime;

	float		m_PatrolLength;
	float		m_CurrentPatrolLength;
	int32		m_CurrentPatrolIndex;

	float		m_DissolveAccTime;
	float		m_DissolveRange;

	bool		m_PatrolEnable;

	class APatrolPointSpline* m_PatrolSpline;

	TArray<FString> m_DropItemNameArray;

	bool IsDead;
public:
	bool m_Boss;
	bool m_BattleStart;

public:
	bool GetPatrolWait();
	FVector GetPatrolPointSpline();

	void SetPatrolEnable(bool Enable)
	{
		m_PatrolEnable = Enable;
	}

	void SetPatrolPointSpline(class APatrolPointSpline* Spline)
	{
		m_PatrolSpline = Spline;
	}

	void SetPatrolLength(float Length)
	{
		m_PatrolLength = Length;
	}

	FVector GetPatrolPoint()
	{
		if (m_PatrolIndex >= m_PatrolArray.Num())
			m_PatrolIndex = 0;

		return m_PatrolArray[m_PatrolIndex];
	}

	void NextPatrolPoint()
	{
		++m_PatrolIndex;
		++m_CurrentPatrolIndex;

		if (m_PatrolIndex >= m_PatrolArray.Num())
			m_PatrolIndex = 0;

		if (m_CurrentPatrolIndex >= 3)
			m_CurrentPatrolIndex = 0;
	}

	EMonsterAnimType GetAnimType()	const;
	void ChangeAnimType(EMonsterAnimType Type);
	
	EMonsterAttackType GetAttackType()	const;
	void ChangeAttackType(EMonsterAttackType Type);
	
	bool GetAttackEnd()	const
	{
		return m_AttackEnd;
	}

	void SetAttackEnd(bool AttackEnd)
	{
		m_AttackEnd = AttackEnd;
	}

	

	void SetSpawnPoint(class AMonsterSpawnPoint* SpawnPoint)
	{
		m_SpawnPoint = SpawnPoint;
	}

	FMonsterInfo& GetMonsterInfo()
	{
		return m_MonsterInfo;
	}

	void AddPatrolPoint(const FVector& Point)
	{
		m_PatrolArray.Add(Point);
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);


public:
	void Death();

public:
	virtual void NormalAttack();

public:
	UFUNCTION()
	void NameWidgetCallback();

public:
	bool MonsterIsDead()
	{
		return IsDead;
	}
};
