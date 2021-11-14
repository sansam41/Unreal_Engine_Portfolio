// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "SelectPlayerAnimInstance.generated.h"

UENUM(BlueprintType)
enum class ESelectPlayerAnimType : uint8
{
	Idle,
	IdleStart,
	Select,
};

/**
 * 
 */
UCLASS()
class UEKR2_API USelectPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
	
	public:
	USelectPlayerAnimInstance();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ESelectPlayerAnimType	m_AnimType;

	
	void ChangeAnimType(ESelectPlayerAnimType Type)
	{
		m_AnimType = Type;
	}

	ESelectPlayerAnimType GetAnimType()
	{
		return m_AnimType;
	}

	public:

	UFUNCTION()
	void AnimNotify_TransitionIdle();
	
	UFUNCTION()
	void AnimNotify_IdleStart();
	
	///virtual void NativeInitializeAnimation();
	//virtual void NativeUpdateAnimation(float DeltaSeconds);
};
