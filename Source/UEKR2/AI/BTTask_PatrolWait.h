// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_PatrolWait.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API UBTTask_PatrolWait : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_PatrolWait();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta=(AllowPrivateAccess="true"))
	float m_WaitTime;

	float m_AccTime;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
