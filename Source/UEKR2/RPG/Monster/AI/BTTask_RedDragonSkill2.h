// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_RedDragonSkill2.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API UBTTask_RedDragonSkill2 : public UBTTaskNode
{
	GENERATED_BODY()
	public:
	UBTTask_RedDragonSkill2();
	~UBTTask_RedDragonSkill2();


	
	protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);	
};
