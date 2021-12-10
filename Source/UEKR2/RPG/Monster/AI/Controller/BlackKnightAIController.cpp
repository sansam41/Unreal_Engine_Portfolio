// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackKnightAIController.h"

ABlackKnightAIController::ABlackKnightAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> AITreeAsset(TEXT("BehaviorTree'/Game/Monster/RPG/AI/BTBlackKnight.BTBlackKnight'"));
	if (AITreeAsset.Succeeded())
		m_AITree = AITreeAsset.Object;
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BlackboardAsset(TEXT("BlackboardData'/Game/Monster/BBMonster.BBMonster'"));
	if (BlackboardAsset.Succeeded())
		m_AIBlackboard = BlackboardAsset.Object;
}


void ABlackKnightAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);


}


void ABlackKnightAIController::OnUnPossess()
{
	Super::OnUnPossess();
}