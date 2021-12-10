// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "Trigger.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTriggerDelegate);

UCLASS(BlueprintType)
class UEKR2_API ATrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrigger();

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	UShapeComponent* m_Trigger;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	ETriggerType m_ShapeType;
		
	UPROPERTY(BlueprintAssignable, Category= "Collision")
	FTriggerDelegate m_TriggerBeginDelegate;
	
	UPROPERTY(BlueprintAssignable, Category= "Collision")
	FTriggerDelegate m_TriggerEndDelegate;

	AActor* m_Other;

public:
	FTriggerDelegate& GetBeginDelegate()
	{
		return m_TriggerBeginDelegate;
	}
	
	FTriggerDelegate& GetEndDelegate()
	{
		return m_TriggerEndDelegate;
	}
	

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	UFUNCTION()
	void TriggerBeginOverlap(UPrimitiveComponent* OverlapCom, AActor* OtherActor,
		UPrimitiveComponent* OtherCom,int32 OtherBodyIndex,bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void TriggerEndOverlap(UPrimitiveComponent* OverlapCom, AActor* OtherActor,
		UPrimitiveComponent* OtherCom,int32 OtherBodyIndex);

public:
	template <typename T>
	void AddBeginTriggerDelegate(T* Obj, void(T::* Func)())
	{
		m_TriggerBeginDelegate.AddDynamic(Obj,Func());
	}
	
	template <typename T>
	void AddEndTriggerDelegate(T* Obj, void(T::* Func)())
	{
		m_TriggerEndDelegate.AddDynamic(Obj,Func());
	}
};
