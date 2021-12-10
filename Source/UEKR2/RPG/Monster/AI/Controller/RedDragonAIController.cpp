// Fill out your copyright notice in the Description page of Project Settings.


#include "RedDragonAIController.h"


ARedDragonAIController::ARedDragonAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> AITreeAsset(TEXT("BehaviorTree'/Game/Monster/RPG/AI/BTRedDragon.BTRedDragon'"));
	if (AITreeAsset.Succeeded())
		m_AITree = AITreeAsset.Object;
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BlackboardAsset(TEXT("BlackboardData'/Game/Monster/BBMonster.BBMonster'"));
	if (BlackboardAsset.Succeeded())
		m_AIBlackboard = BlackboardAsset.Object;
}


void ARedDragonAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);


}


void ARedDragonAIController::OnUnPossess()
{
	Super::OnUnPossess();
}