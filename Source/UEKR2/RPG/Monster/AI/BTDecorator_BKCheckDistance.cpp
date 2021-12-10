// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_BKCheckDistance.h"
#include "../../../Monster/Monster.h"
#include "../../../Monster/MonsterAIController.h"
#include "UEKR2/RPG/Monster/RPG_BlackKnight.h"
#include "UEKR2/RPG/Player/RPG_PlayerCharacter.h"

UBTDecorator_BKCheckDistance::UBTDecorator_BKCheckDistance() 
{
	NodeName = TEXT("BKCheckDistance");
}

bool UBTDecorator_BKCheckDistance::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool result = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	if (!Controller)
		return false;

	ARPG_BlackKnight* Monster = Cast<ARPG_BlackKnight>(Controller->GetPawn());

	if (!Monster)
		return false;

	//APlayerCharacter* Target = Cast<APlayerCharacter>(Controller->GetBlackboardComponent()->GetValueAsObject(("Target")));
	ARPG_PlayerCharacter* Target = Cast<ARPG_PlayerCharacter>(Controller->GetBlackboardComponent()->GetValueAsObject(("Target")));

	if (!Target)
		return false;

	const FMonsterInfo& MonsterInfo = Monster->GetMonsterInfo();
	
	// 타겟과의 거리를 구한다.
	FVector MonsterLoc = Monster->GetActorLocation();
	FVector TargetLoc = Target->GetActorLocation();

	MonsterLoc.Z = TargetLoc.Z;
	float Distance = FVector::Distance(MonsterLoc, TargetLoc);
	float CheckDist = 0.f;
	
	if(Monster->SkillOn)
	{
		return true;
	}
	
	switch (m_CheckType)
	{
	case ECheckDistanceType::Trace:
		CheckDist = MonsterInfo.TraceDistance;
		break;
	case ECheckDistanceType::Attack:
		CheckDist = MonsterInfo.AttackDistance;
		break;
	}
	return Distance<=CheckDist;
}