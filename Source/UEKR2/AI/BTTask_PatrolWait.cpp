// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_PatrolWait.h"

#include "../Monster/Monster.h"
#include "../Monster/MonsterAIController.h"


UBTTask_PatrolWait::UBTTask_PatrolWait()
{
	NodeName=TEXT("PatrolWait");
	bNotifyTick=true;

	m_WaitTime=1.f;
	m_AccTime=0.f;
}


EBTNodeResult::Type UBTTask_PatrolWait::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result =Super::ExecuteTask(OwnerComp, NodeMemory);

	AMonsterAIController* Controller=Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	if(!Controller)
		return EBTNodeResult::Failed;

	AMonster* Monster = Cast<AMonster>(Controller->GetPawn());

	if(!Monster)
		return EBTNodeResult::Failed;



	Monster->ChangeAnimType(EMonsterAnimType::Idle);

	return EBTNodeResult::InProgress;
}




EBTNodeResult::Type UBTTask_PatrolWait::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result=Super::AbortTask(OwnerComp, NodeMemory);
	return result;
}



void UBTTask_PatrolWait::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	if(!Controller)
	{
		FinishLatentTask(OwnerComp,EBTNodeResult::Failed);
		return;
	}
	AMonster *Monster=Cast<AMonster>(Controller->GetPawn());

	if(!Monster)
	{
		FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
		return;
	}



	m_AccTime+=DeltaSeconds;
	if(m_AccTime>=m_WaitTime)
	{
		m_AccTime = 0.f;
		FinishLatentTask(OwnerComp,EBTNodeResult::Failed);
		
	}
	
}