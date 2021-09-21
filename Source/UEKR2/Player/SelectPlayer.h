// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerCharacter.h"
#include "SelectPlayerAnimInstance.h"
#include "../GameInfo.h"
#include "GameFramework/Character.h"

#include "SelectPlayer.generated.h"

UCLASS()
class UEKR2_API ASelectPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASelectPlayer();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EPlayerJob m_Job;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FPlayerInfo m_PlayerInfo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USelectPlayerAnimInstance* m_AnimInstance;
	
public:
	EPlayerJob GetPlayerJob() const
	{
		return m_Job;
	}
	void SetPlayerAnimSelect()
	{
		m_AnimInstance->ChangeAnimType(ESelectPlayerAnimType::Select);
	}
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
