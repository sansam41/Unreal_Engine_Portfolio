// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../../GameInfo.h"
#include "../../../../Monster/MonsterAIController.h"
#include "NormalMonsterAIController.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API ANormalMonsterAIController : public AMonsterAIController
{
	GENERATED_BODY()
public:
	ANormalMonsterAIController();


protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
};
