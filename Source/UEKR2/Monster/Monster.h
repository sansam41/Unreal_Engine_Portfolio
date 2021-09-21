// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Character.h"
#include "MonsterAnimInstance.h"
#include "Components/WidgetComponent.h"
#include "Monster.generated.h"


USTRUCT(BlueprintType)
struct FMonsterInfo {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 Attack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 Armor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 HP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 HPMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 MP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 MPMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 Exp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 Gold;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float AttackDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float AttackSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MoveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float AttackAngle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float TraceDistance;



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
	FMonsterInfo m_MonsterInfo;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess="true"))
	UWidgetComponent* m_HPBar;

	class UHPBar* m_HPBarWidget;
	

	class AMonsterSpawnPoint* m_SpawnPoint;


	FString m_MonsterInfoName;

	class UMonsterAnimInstance* m_AnimInstance;

	bool	m_AttackEnd;

	TArray<FVector> m_PatrolArray;
	int32 m_PatrolIndex;


public:

	FVector GetPatrolPoint()
	{
		if(m_PatrolIndex>=m_PatrolArray.Num())
			m_PatrolIndex=0;
		return m_PatrolArray[m_PatrolIndex];	
	}

	void NextPatrolPoint()
	{
		++m_PatrolIndex;

		if(m_PatrolIndex>=m_PatrolArray.Num())
		{
			m_PatrolIndex=0;
		}
	}
	
	
	EMonsterAnimType GetAnimType() const;

	bool GetAttackEnd() const{
		return m_AttackEnd;
	}

	void SetAttackEnd(bool AttackEnd) {
		m_AttackEnd = AttackEnd;		
	}

	void ChangeAnimType(EMonsterAnimType Type);

	void SetSpawnPoint(class AMonsterSpawnPoint* SpawnPoint) {
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

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	void Death();

public:
	virtual void NormalAttack();

public:
	UFUNCTION()
	void NameWidgetCallback();
};
