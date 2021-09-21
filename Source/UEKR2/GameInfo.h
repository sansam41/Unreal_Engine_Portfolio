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
FString : 언리얼엔진에서 제공되는 문자열 타입이다.
FString은 앞에 * 을 붙여주면 이 FString이 실제 가지고 있는 문자열의 주소를 의미한다.
__FUNCTION__ : 현재 이 로그를 출력하는 함수 이름을 의미한다.
__LINE : 현재 코드의 줄번호를 의미한다.
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


