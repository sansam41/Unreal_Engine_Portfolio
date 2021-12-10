// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_BlackKnightAttack.h"
#include "../../../Monster/Monster.h"
#include "../../../Monster/MonsterAIController.h"
#include "UEKR2/RPG/Monster/RPG_BlackKnight.h"
#include "UEKR2/RPG/Player/RPG_PlayerCharacter.h"

UBTTask_BlackKnightAttack::UBTTask_BlackKnightAttack()
{
	NodeName = TEXT("BlackKnightAttack");
	bNotifyTick = true;
}
UBTTask_BlackKnightAttack::~UBTTask_BlackKnightAttack()
{
}


EBTNodeResult::Type UBTTask_BlackKnightAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	if (!Controller)
		return EBTNodeResult::Failed;


	ARPG_BlackKnight* Monster = Cast<ARPG_BlackKnight>(Controller->GetPawn());

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
	
	if(Monster->SkillOn)
	{
		FVector MonsterLoc = Monster->GetActorLocation();
		FVector TargetLoc = Target->GetActorLocation();
		MonsterLoc.Z = TargetLoc.Z;
		FVector Dir = TargetLoc - MonsterLoc;
		Dir.Normalize();
		Monster->SetActorRotation(FRotator(0.f, Dir.Rotation().Yaw, 0.f));
		Monster->ChangeAttackType(EMonsterAttackType::Attack2);
		Monster->SkillOn =false;
	}
	else
	{
		Monster->ChangeAttackType(EMonsterAttackType::Attack1);
	}
	
	
	Monster->ChangeAnimType(EMonsterAnimType::Attack);


	return EBTNodeResult::InProgress;
}


EBTNodeResult::Type UBTTask_BlackKnightAttack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::AbortTask(OwnerComp, NodeMemory);
	return result;
}


void UBTTask_BlackKnightAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	

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

	// 타겟과의 거리를 구한다.
	FVector MonsterLoc = Monster->GetActorLocation();
	FVector TargetLoc = Target->GetActorLocation();

	MonsterLoc.Z = TargetLoc.Z;

	float Distance = FVector::Distance(MonsterLoc, TargetLoc);



	if (Monster->GetAttackEnd())
	{
		if(Monster->SkillOn)
		{
			Monster->ChangeAttackType(EMonsterAttackType::Attack2);
			Monster->SkillOn =false;
		}
		else
		{
			Monster->ChangeAttackType(EMonsterAttackType::Attack1);
		}
		
		if (Distance > MonsterInfo.AttackDistance)
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		}
		else 
		{
			FVector Dir = TargetLoc - MonsterLoc;
			Dir.Normalize();
			Monster->SetActorRotation(FRotator(0.f, Dir.Rotation().Yaw, 0.f));
		}
		Monster->SetAttackEnd(false);
		return;
	}
}