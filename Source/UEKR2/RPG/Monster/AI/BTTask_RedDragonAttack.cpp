// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_RedDragonAttack.h"

#include "../../../Monster/Monster.h"
#include "../../../Monster/MonsterAIController.h"
#include "UEKR2/RPG/Monster/RPG_RedDragon.h"
#include "UEKR2/RPG/Player/RPG_PlayerCharacter.h"

UBTTask_RedDragonAttack::UBTTask_RedDragonAttack()
{
	NodeName = TEXT("RedDragonAttack");
	bNotifyTick = true;
}
UBTTask_RedDragonAttack::~UBTTask_RedDragonAttack()
{
}


EBTNodeResult::Type UBTTask_RedDragonAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	if (!Controller)
		return EBTNodeResult::Failed;


	ARPG_RedDragon* Monster = Cast<ARPG_RedDragon>(Controller->GetPawn());

	if (!Monster)
		return EBTNodeResult::Failed;
	
	if(Monster->AttackOn==false)
		return EBTNodeResult::Failed;

	//APlayerCharacter* Target = Cast<APlayerCharacter>(Controller->GetBlackboardComponent()->GetValueAsObject(("Target")));
	ARPG_PlayerCharacter* Target = Cast<ARPG_PlayerCharacter>(Controller->GetBlackboardComponent()->GetValueAsObject(("Target")));

	if (!Target)
	{
		Monster->ChangeAnimType(EMonsterAnimType::Idle);
		Controller->StopMovement();
		return EBTNodeResult::Failed;
	}
	
	// 타겟과의 거리를 구한다.
	FVector MonsterLoc = Monster->GetActorLocation();
	FVector TargetLoc = Target->GetActorLocation();

	MonsterLoc.Z = TargetLoc.Z;

	float Distance = FVector::Distance(MonsterLoc, TargetLoc);
	FVector Dir = TargetLoc - MonsterLoc;
	Dir.Normalize();

	Monster->SetActorRotation(FRotator(0.f, Dir.Rotation().Yaw, 0.f));
	Monster->ChangeAttackType(EMonsterAttackType::Attack1);
	
	
	Monster->AttackOn = false;
	Monster->ChangeAnimType(EMonsterAnimType::Attack);


	return EBTNodeResult::InProgress;
}


EBTNodeResult::Type UBTTask_RedDragonAttack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::AbortTask(OwnerComp, NodeMemory);
	return result;
}


void UBTTask_RedDragonAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	

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
	// 타겟과의 거리를 구한다.
	FVector MonsterLoc = Monster->GetActorLocation();
	FVector TargetLoc = Target->GetActorLocation();

	MonsterLoc.Z = TargetLoc.Z;

	float Distance = FVector::Distance(MonsterLoc, TargetLoc);
	FVector Dir = TargetLoc - MonsterLoc;
	Dir.Normalize();


	if (Monster->GetAttackEnd())
	{
		if(Monster->AttackOn)
		{
			Monster->ChangeAttackType(EMonsterAttackType::Attack1);
			Monster -> SetActorRotation(FMath::Lerp(Monster->GetActorRotation(),FRotator(0.f, Dir.Rotation().Yaw, 0.f),0.05f));
	

			Monster->AttackOn =false;
		}
		else
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		}
		
		if (Distance > MonsterInfo.AttackDistance)
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		}/*
		else 
		{
			FVector Dir = TargetLoc - MonsterLoc;
			Dir.Normalize();
			Monster->SetActorRotation(FRotator(0.f, Dir.Rotation().Yaw, 0.f));
		}*/
		Monster->SetAttackEnd(false);
		return;
	}
}