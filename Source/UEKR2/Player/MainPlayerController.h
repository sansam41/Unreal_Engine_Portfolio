// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/PlayerController.h"
#include "UEKR2/Environment/EnvironmentNormalActor.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMainPlayerController();
private:
	TArray<class AEnvironmentNormalActor*> m_CollisionEnvironmentActor;
public:
	bool m_ShowUI;
public:
	virtual void PlayerTick(float DeltaTime) override;
	
	
};

