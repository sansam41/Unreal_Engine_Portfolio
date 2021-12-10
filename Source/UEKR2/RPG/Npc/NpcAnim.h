// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "NpcAnim.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ENpcAnimType : uint8
{
	Idle,
	Walk,
	Hi,
	Bye,
};

UCLASS()
class UEKR2_API UNpcAnim : public UAnimInstance
{
	GENERATED_BODY()
public:
	UNpcAnim();
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ENpcAnimType	m_AnimType;

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

public:
	ENpcAnimType GetAnimType() const
	{
		return m_AnimType;
	}
};
