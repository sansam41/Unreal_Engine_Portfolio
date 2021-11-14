// Fill out your copyright notice in the Description page of Project Settings.
//
#pragma once

#include "EngineMinimal.h"
#include "DrawDebugHelpers.h"
#include "DestructibleComponent.h"
#include "Engine.h"
#include "Engine/AssetManager.h"
#include "EngineGlobals.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "MediaPlayer.h"
#include "MediaTexture.h"
#include "MediaSoundComponent.h"
#include "MediaSource.h"
#include "Components/SplineComponent.h"
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "HAL/Runnable.h"
#include "HAL/RunnableThread.h"
#include "Blueprint/IUserObjectListEntry.h"

#include "GameInfo.generated.h"


#define PACKET_SIZE 1024
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
#define	LOGSTRING(Str)		UE_LOG(UEKR2, Warning, TEXT("%s : %s"), *LOG_CALLINFO, *Str)

void PrintViewport(float Time, const FColor& Color, const FString& Text);
//PrintViewport(1.f,FColor::Red,TEXT("in"));
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

UENUM(BlueprintType)
enum class EItemOption : uint8
{
	Attack,
	Armor,
	HPMax,
	MPMax,
	HPRecovery,
	MPRecovery,
	Critical
};


// 아이템이 겹쳐지는지 여부
UENUM(BlueprintType)
enum class EItemOverlap : uint8
{
	None,
	Overlap
};

// 아이템이 겹쳐지는지 여부
UENUM(BlueprintType)
enum class EItemType : uint8
{
	Weapon,
	Armor,
	Potion
};


USTRUCT(BlueprintType)
struct FItemOption
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EItemOption	OptionType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	Option;
	
};
USTRUCT(BlueprintType)
struct FUIItemTableInfo : public FTableRowBase 
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString Name;							//아이템 이름
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EItemOverlap Overlap;					//아이템 오버랩 유무
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EItemType ItemType;						//아이템 타입

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTexture2D* IconTexture;				//아이템 아이콘
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMesh* Mesh;						//아이템 메쉬
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString Type;							//아이템 타입
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString Desc;							//아이템 설명
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<FItemOption> OptionArray;		//아이템 옵션
};

UENUM(BlueprintType)
enum class EQuestType : uint8
{
	Collection,
	Hunt,
	Communication,
	Max
};

USTRUCT(BlueprintType)
struct FQuestInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EQuestType Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString DestName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 Count;
};


USTRUCT(BlueprintType)
struct FQuestTableInfo : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString QuestDesc;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<FQuestInfo> InfoArray;					
};

struct FQuestDataInfo
{
	EQuestType Type;
	FString DestName;
	int32 Count;
	int32 MaxCount;
	bool Complete;
};

struct FQuestData
{
	FString Name;
	FString QuestDesc;
	TArray<FQuestDataInfo>	CompleteArray;
	bool Complete;
	
};


USTRUCT()
struct FAssetPathInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Path")
	FString		Name;

	UPROPERTY(EditAnywhere, Category = "Path")
	FSoftObjectPath		Path;
};

struct RecvQueueData
{
	int32	Protocol;
	int32	Length;
	uint8	Packet[PACKET_SIZE];

	RecvQueueData()	:
		Protocol(-1),
		Length(0),
		Packet{}
	{
	}
};

enum class NetworkProtocol
{
	Chat,
	UserConnect
};



