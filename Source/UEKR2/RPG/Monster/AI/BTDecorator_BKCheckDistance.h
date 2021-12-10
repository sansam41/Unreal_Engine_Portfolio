// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_BKCheckDistance.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API UBTDecorator_BKCheckDistance : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_BKCheckDistance();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ECheckDistanceType m_CheckType;
public:

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;
	
};
