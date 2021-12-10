// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_BlackKnightTrace.h"
#include "../../../Player/PlayerCharacter.h"
#include "../../../Monster/Monster.h"
#include "../../../Monster/MonsterAIController.h"
#include "UEKR2/RPG/Monster/RPG_BlackKnight.h"
#include "UEKR2/RPG/Player/RPG_PlayerCharacter.h"

UBTTask_BlackKnightTrace::UBTTask_BlackKnightTrace()
{
	NodeName = TEXT("BlackKnightTrace");
	bNotifyTick = true;
}
UBTTask_BlackKnightTrace::~UBTTask_BlackKnightTrace()
{
}

EBTNodeResult::Type UBTTask_BlackKnightTrace::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	if (!Controller)
		return EBTNodeResult::Failed;
	

	AMonster* Monster = Cast<AMonster>(Controller->GetPawn());

	if (!Monster)
		return EBTNodeResult::Failed;


	//APlayerCharacter* Target = Cast<APlayerCharacter>(Controller->GetBlackboardComponent()->GetValueAsObject(("Target")));
	ARPG_PlayerCharacter* Target = Cast<ARPG_PlayerCharacter>(Controller->GetBlackboardComponent()->GetValueAsObject(("Target")));

	if (!Target)
	{
		Monster->ChangeAnimType(EMonsterAnimType::Idle);
		Controller->StopMovement();
		return EBTNodeResult::Failed;
	}


	Monster->GetCharacterMovement()->MaxWalkSpeed = Monster->GetMonsterInfo().MoveSpeed;
	UAIBlueprintHelperLibrary::SimpleMoveToActor(Controller, Target);
	Monster->ChangeAnimType(EMonsterAnimType::Run);


	
	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UBTTask_BlackKnightTrace::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::AbortTask(OwnerComp, NodeMemory);
	return result;
}

void UBTTask_BlackKnightTrace::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);


	
	// InProgress�� �صξ��� ������ ���⼭ �ȳ�����.
	// �׷��� ���ݰŸ� �ȿ� ���Դ����� ���⼭�� üũ�Ͽ� ���ٸ�
	// Trace�� �����Ų��.

	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	if (!Controller)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}	

	ARPG_BlackKnight* Monster = Cast<ARPG_BlackKnight>(Controller->GetPawn());

	if (!Monster)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}
	
	//APlayerCharacter* Target = Cast<APlayerCharacter>(Controller->GetBlackboardComponent()->GetValueAsObject(("Target")));
	ARPG_PlayerCharacter* Target = Cast<ARPG_PlayerCharacter>(Controller->GetBlackboardComponent()->GetValueAsObject(("Target")));
	if (!Target)
	{
		Monster->ChangeAnimType(EMonsterAnimType::Idle);
		Controller->StopMovement();
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}
	

	const FMonsterInfo& MonsterInfo = Monster->GetMonsterInfo();

	FVector MonsterLoc = Monster->GetActorLocation();
	FVector TargetLoc = Target->GetActorLocation();

	MonsterLoc.Z = TargetLoc.Z;

	float Distance = FVector::Distance(MonsterLoc, TargetLoc);

	UAIBlueprintHelperLibrary::SimpleMoveToActor(Controller, Target);


	if(Monster->SkillOn)
	{
		Controller->StopMovement();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}
	if (Distance <= MonsterInfo.AttackDistance)
	{
		Controller->StopMovement();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}
}