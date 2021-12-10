// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "UEKR2/RPG/Player/RPG_PlayerCharacter.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "NpcBase.generated.h"



USTRUCT(BlueprintType)
struct FNpcInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString			Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int			Type;	// 1: Quest 2: Seller
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<FString>	Dialogue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<FString>	Dialogue2;

	
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNpcTalkDelegate);

UCLASS(BlueprintType)
class UEKR2_API ANpcBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANpcBase();
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FNpcInfo	m_NpcInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* m_NpcInfoBar;

	class UNpcInfoBar* m_NpcInfoBarWidget;

	
	class ARPG_PlayerCharacter* Player;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	int32 m_QuestProgress;

	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	int32 m_DialogueProgress;

protected:
	bool m_ordered;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	
public:
	UFUNCTION()
	void NameWidgetCallback();
	//UFUNCTION()
	//void DialogueWidgetCallback();

	
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	UShapeComponent* m_Trigger;
	
		
	UPROPERTY(BlueprintAssignable, Category= "Collision")
	FNpcTalkDelegate m_TriggerBeginDelegate;
	
	UPROPERTY(BlueprintAssignable, Category= "Collision")
	FNpcTalkDelegate m_TriggerEndDelegate;

	public:
	FNpcTalkDelegate& GetBeginDelegate()
	{
		return m_TriggerBeginDelegate;
	}
	
	FNpcTalkDelegate& GetEndDelegate()
	{
		return m_TriggerEndDelegate;
	}


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

public:
	void SetDialogue();
	bool GetOrdered()
	{
		return m_ordered;
	}
	void SetOrdered(bool ordered)
	{
		m_ordered = ordered;
	}

	ARPG_PlayerCharacter* GetPlayer()
	{
		return Player;
	}
};
