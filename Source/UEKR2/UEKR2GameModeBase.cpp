// Copyright Epic Games, Inc. All Rights Reserved.


#include "UEKR2GameModeBase.h"
#include "UEKR2GameInstance.h"
#include "Player/MainPlayerController.h"


AUEKR2GameModeBase::AUEKR2GameModeBase() {
	// UClass: UObject를 상속받은 언리얼엔진 클래스들은 모두 UClass를 가지고 있다.
	// UClass는 자신이 어떤 클래스 타입잉ㄴ지에 대한 클래스 정보를 가지고 있다.
	// 그래서 언리얼엔진의 객체를 생성할 때는 어떤 타입인지 UClass정보를 넘겨서 생성하도록
	// 되어 있다.
	// GameMode에서 PlayerController와 DefaultPawn의 경우 모두 UClass를 지정하게끔
	// 만들어져 있다.
	// ClassFinder를 할 때는 경로의 마지막에 반드시 _C를 붙여야 한다.
	PrimaryActorTick.bCanEverTick=true;
	
	ConstructorHelpers::FClassFinder<APawn> KnightClass(TEXT("Blueprint'/Game/Player/BPGreystone.BPGreystone_C'"));

	if(KnightClass.Succeeded())
		m_PlayerClassArray.Add(KnightClass.Class);
	
	ConstructorHelpers::FClassFinder<APawn> ArcherClass(TEXT("Blueprint'/Game/Player/BPWraith.BPWraith_C'"));

	if(ArcherClass.Succeeded())
		m_PlayerClassArray.Add(ArcherClass.Class);
	ConstructorHelpers::FClassFinder<APawn> MageClass(TEXT("Blueprint'/Game/Player/BPWraith.BPWraith_C'"));

	if(MageClass.Succeeded())
		m_PlayerClassArray.Add(MageClass.Class);

	static ConstructorHelpers::FClassFinder<UMainHUD> MainHUDClass(TEXT("WidgetBlueprint'/Game/UI/UI_MainHUD.UI_MainHUD_C'"));
	if(MainHUDClass.Succeeded())
		m_MainHUDClass=MainHUDClass.Class;

	PlayerControllerClass = AMainPlayerController::StaticClass();
}

void AUEKR2GameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	UUEKR2GameInstance* GameInst = Cast<UUEKR2GameInstance>(GetWorld()->GetGameInstance());

	if (GameInst)
	{
		EPlayerJob SelectJob = GameInst->GetSelectJob();

		switch (SelectJob)
		{
		case EPlayerJob::Knight:
			{
				DefaultPawnClass = m_PlayerClassArray[0];
			}
			break;
		case EPlayerJob::Archer:
			{
				DefaultPawnClass = m_PlayerClassArray[1];
			}
			break;
		case EPlayerJob::Mage:
			{
				DefaultPawnClass = m_PlayerClassArray[2];
			}
			break;
		}
	}

}
void AUEKR2GameModeBase::BeginPlay()
{
	Super::BeginPlay();
	if(IsValid(m_MainHUDClass))
	{
		m_MainHUD=Cast<UMainHUD>(CreateWidget(GetWorld(),
			m_MainHUDClass));

		if(m_MainHUD)
			m_MainHUD->AddToViewport();
	}

	AMainPlayerController* Controller = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
	
	FInputModeGameOnly	Mode;

	Controller->SetInputMode(Mode);
	Controller->bShowMouseCursor = false;

	//Mode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	//EMouseLockMode::LockOnCapture
}

void AUEKR2GameModeBase::Tick(float DeltaSeconds)
{
	AMainPlayerController* Controller = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());


	m_MainHUD->ShowUI(Controller->m_ShowUI);
	
}