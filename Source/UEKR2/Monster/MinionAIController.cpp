// Fill out your copyright notice in the Description page of Project Settings.


#include "MinionAIController.h"

AMinionAIController::AMinionAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> AITreeAsset(TEXT("BehaviorTree'/Game/Monster/RPG/AI/BTNormalMonster.BTNormalMonster'"));
	if (AITreeAsset.Succeeded())
		m_AITree = AITreeAsset.Object;
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BlackboardAsset(TEXT("BlackboardData'/Game/Monster/BBMonster.BBMonster'"));
	if (BlackboardAsset.Succeeded())
		m_AIBlackboard = BlackboardAsset.Object;
}
void AMinionAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);


}
void AMinionAIController::OnUnPossess()
{
	Super::OnUnPossess();
}