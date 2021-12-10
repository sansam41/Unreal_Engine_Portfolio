// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_RedDragonTrace.h"

#include "../../../Player/PlayerCharacter.h"
#include "../../../Monster/Monster.h"
#include "../../../Monster/MonsterAIController.h"
#include "UEKR2/RPG/Monster/RPG_RedDragon.h"
#include "UEKR2/RPG/Player/RPG_PlayerCharacter.h"

UBTTask_RedDragonTrace::UBTTask_RedDragonTrace()
{
	NodeName = TEXT("RedDragonTrace");
	bNotifyTick = true;
}
UBTTask_RedDragonTrace::~UBTTask_RedDragonTrace()
{
}

EBTNodeResult::Type UBTTask_RedDragonTrace::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

EBTNodeResult::Type UBTTask_RedDragonTrace::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::AbortTask(OwnerComp, NodeMemory);
	return result;
}

void UBTTask_RedDragonTrace::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);


	
	// InProgress로 해두었기 때문에 여기서 안나간다.
	// 그래서 공격거리 안에 들어왔는지를 여기서도 체크하여 들어갔다면
	// Trace를 종료시킨다.

	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	if (!Controller)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}	

	ARPG_RedDragon* Monster = Cast<ARPG_RedDragon>(Controller->GetPawn());

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
	FVector Dir = TargetLoc - MonsterLoc;
	Dir.Normalize();

	Monster -> SetActorRotation(FMath::Lerp(Monster->GetActorRotation(),FRotator(0.f, Dir.Rotation().Yaw, 0.f),0.05f));
	UAIBlueprintHelperLibrary::SimpleMoveToActor(Controller, Target);



	if (Distance <= MonsterInfo.AttackDistance&&Monster->AttackOn)
	{
		Controller->StopMovement();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}
	else if (Distance >= MonsterInfo.AttackDistance&&Distance <= Monster->Skill1Distance&&Monster->Skill1On)
	{
		Controller->StopMovement();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}
	else if (Distance >= MonsterInfo.AttackDistance&&Distance <= Monster->Skill2Distance&&Monster->Skill2On)
	{
		Controller->StopMovement();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}
}