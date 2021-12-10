// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_RedDragonTrace.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API UBTTask_RedDragonTrace : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_RedDragonTrace();
	~UBTTask_RedDragonTrace();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);	
};
