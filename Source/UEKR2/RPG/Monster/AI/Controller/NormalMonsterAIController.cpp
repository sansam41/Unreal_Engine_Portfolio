// Fill out your copyright notice in the Description page of Project Settings.


#include "NormalMonsterAIController.h"


ANormalMonsterAIController::ANormalMonsterAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> AITreeAsset(TEXT("BehaviorTree'/Game/Monster/BTMinion.BTMinion'"));
	if (AITreeAsset.Succeeded())
		m_AITree = AITreeAsset.Object;
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BlackboardAsset(TEXT("BlackboardData'/Game/Monster/BBMonster.BBMonster'"));
	if (BlackboardAsset.Succeeded())
		m_AIBlackboard = BlackboardAsset.Object;
}


void ANormalMonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);


}


void ANormalMonsterAIController::OnUnPossess()
{
	Super::OnUnPossess();
}