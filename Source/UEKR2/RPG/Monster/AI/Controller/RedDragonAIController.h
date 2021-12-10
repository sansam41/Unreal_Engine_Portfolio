// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../../GameInfo.h"
#include "../../../../Monster/MonsterAIController.h"
#include "RedDragonAIController.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API ARedDragonAIController : public AMonsterAIController
{
	GENERATED_BODY()
public:
	ARedDragonAIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
};
