// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Patrol.h"
#include "../Player/PlayerCharacter.h"
#include "../Monster/Monster.h"
#include "../Monster/MonsterAIController.h"


UBTTask_Patrol::UBTTask_Patrol()
{
	NodeName=TEXT("Patrol");
	bNotifyTick=true;
}


EBTNodeResult::Type UBTTask_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result =Super::ExecuteTask(OwnerComp, NodeMemory);

	AMonsterAIController* Controller=Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	if(!Controller)
		return EBTNodeResult::Failed;

	AMonster* Monster = Cast<AMonster>(Controller->GetPawn());

	if(!Monster)
		return EBTNodeResult::Failed;

	APlayerCharacter* Target = Cast<APlayerCharacter>(Controller->GetBlackboardComponent()->GetValueAsObject(("Target")));

	if (Target)
	{
		return EBTNodeResult::Failed;
	}

	Monster->ChangeAnimType(EMonsterAnimType::Walk);

	Monster->GetCharacterMovement()->MaxWalkSpeed = Monster->GetMonsterInfo().MoveSpeed * 0.5f;
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controller,Monster->GetPatrolPoint());
	


	return EBTNodeResult::InProgress;
}




EBTNodeResult::Type UBTTask_Patrol::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result=Super::AbortTask(OwnerComp, NodeMemory);
	return result;
}



void UBTTask_Patrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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
		FinishLatentTask(OwnerComp,EBTNodeResult::Failed);
		return;
	}

	APlayerCharacter* Target = Cast<APlayerCharacter>(Controller->GetBlackboardComponent()->GetValueAsObject(("Target")));

	if (Target)
	{
		FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
	}


	// 도착했다면.
	FVector	PatrolPoint = Monster->GetPatrolPoint();
	FVector	MonsterLoc = Monster->GetActorLocation();

	float	CapsuleHalfHeight = Monster->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
	float	CapsuleRadius = Monster->GetCapsuleComponent()->GetUnscaledCapsuleRadius();

	float	Distance = FVector::Distance(MonsterLoc, PatrolPoint);

	if (Distance <= CapsuleHalfHeight + CapsuleRadius)
	{
		Monster->NextPatrolPoint();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	
}