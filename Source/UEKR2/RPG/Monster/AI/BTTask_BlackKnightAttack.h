// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_BlackKnightAttack.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API UBTTask_BlackKnightAttack : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_BlackKnightAttack();
	~UBTTask_BlackKnightAttack();


	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
};