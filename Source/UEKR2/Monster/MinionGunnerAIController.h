// Fill out your copyright notice in the Description page of Project Settings.

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MinionAIController.h"
#include "MinionGunnerAIController.generated.h"

/**
* 
*/
UCLASS()
class UEKR2_API AMinionGunnerAIController : public AMinionAIController
{
	GENERATED_BODY()

	public:
	AMinionGunnerAIController();

	protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
};
