// Fill out your copyright notice in the Description page of Project Settings.
//
#pragma once

#include "EngineMinimal.h"
#include "DrawDebugHelpers.h"
#include "DestructibleComponent.h"
#include "Engine.h"
#include "EngineGlobals.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "GameInfo.generated.h"

/*
FString : �𸮾������� �����Ǵ� ���ڿ� Ÿ���̴�.
FString�� �տ� * �� �ٿ��ָ� �� FString�� ���� ������ �ִ� ���ڿ��� �ּҸ� �ǹ��Ѵ�.
__FUNCTION__ : ���� �� �α׸� ����ϴ� �Լ� �̸��� �ǹ��Ѵ�.
__LINE : ���� �ڵ��� �ٹ�ȣ�� �ǹ��Ѵ�.
*/

//	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))

DECLARE_LOG_CATEGORY_EXTERN(UEKR2, Log, All);
#define LOG_CALLINFO	(FString(__FUNCTION__)+TEXT("{")+FString::FromInt(__LINE__)+TEXT("}"))
#define LOG(Format, ...) UE_LOG(UEKR2,Warning,TEXT("%s : %s"),*LOG_CALLINFO,*FString::Printf(Format,##__VA_ARGS__))

void PrintViewport(float Time, const FColor& Color, const FString& Text);

UENUM(BlueprintType)
enum class EPlayerJob : uint8 {
	Knight,
	Archer,
	Mage,
	End,
};

UENUM(BlueprintType)
enum class ECheckDistanceType :uint8
{
	Trace,
	Attack,

};

UENUM(BlueprintType)
enum class ETriggerType :uint8
{
	Box,
	Sphere,
	Capsule

};



USTRUCT(BlueprintType)
struct FPlayerInfo {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EPlayerJob Job;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 Attack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 Armor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 HP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 HPMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 MP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 MPMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 Exp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 Gold;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float AttackDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float AttackSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MoveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float 	AttackAngle;



};

USTRUCT(BlueprintType)
struct FUIItemTableInfo : public FTableRowBase 
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString IconPath;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString Type;
};


