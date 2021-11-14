// Fill out your copyright notice in the Description page of Project Settings.


#include "MinionGunnerAIController.h"

AMinionGunnerAIController::AMinionGunnerAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>	AITreeAsset(TEXT("BehaviorTree'/Game/Monster/BTMinionGunner.BTMinionGunner'"));

	if (AITreeAsset.Succeeded())
		m_AITree = AITreeAsset.Object;

	static ConstructorHelpers::FObjectFinder<UBlackboardData>	BlackboardAsset(TEXT("BlackboardData'/Game/Monster/BBMonster.BBMonster'"));

	if (BlackboardAsset.Succeeded())
		m_AIBlackboard = BlackboardAsset.Object;
}

void AMinionGunnerAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AMinionGunnerAIController::OnUnPossess()
{
	Super::OnUnPossess();
}


