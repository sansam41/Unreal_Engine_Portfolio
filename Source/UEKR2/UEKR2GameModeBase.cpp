// Copyright Epic Games, Inc. All Rights Reserved.


#include "UEKR2GameModeBase.h"
#include "UEKR2GameInstance.h"
#include "AssetManager/AssetPathMain.h"
#include "Network/NetworkManager.h"
#include "Network/PacketStream.h"
#include "Network/RecvQueue.h"
#include "UI/ChatWidget.h"
#include "Player/MainPlayerController.h"
#include "User/UserKnightCharacter.h"


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


	m_MainAssetPath = UAssetPathMain::StaticClass()->GetDefaultObject<UAssetPathMain>();

	m_MainAssetPath->ConvertPath();

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
	Super::Tick(DeltaSeconds);
	RecvQueue* Queue = NetworkManager::GetInst()->GetQueue();

	while(!Queue->Empty())
	{
		int32 Protocol = -1,Length = 0;
		uint8 Packet[PACKET_SIZE]={};

		if(Queue->Pop(Protocol,Length, Packet))
		{
			switch((NetworkProtocol)Protocol)
			{
			case NetworkProtocol::Chat:
				{	// 채팅 메세지가 왔을 경우 해당 메세지를 채팅창에 전달
					TCHAR	Msg[1024]={};

					FMemory::Memcpy(Msg,Packet,Length);

					m_MainHUD->GetChatWidget()->AddMsg(Msg);
					
					break;
				}
			case NetworkProtocol::UserConnect:
				{
					// 여기에 들어오면 다른 유저가 접속했다는 것이다.
					// 그러므로 해당 유저를 생성해 주도록 한다.
					PacketStream	stream;
					stream.SetBuffer(Packet);

					EPlayerJob	Job;
					stream.Read(&Job, 4);

					FVector	Pos, Scale;
					FRotator	Rot;

					stream.Read(&Pos, 12);
					stream.Read(&Scale, 12);
					stream.Read(&Rot, 12);

					AUserCharacter* User = nullptr;

					switch (Job)
					{
					case EPlayerJob::Knight:
						{
							FActorSpawnParameters	param;
							param.SpawnCollisionHandlingOverride =
								ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
							User = GetWorld()->SpawnActor<AUserKnightCharacter>(
								AUserKnightCharacter::StaticClass(), Pos + FVector(0.f, -200.f, 0.f), Rot,
								param);
							User->SetActorScale3D(Scale);

							PrintViewport(1.f, FColor::Red, TEXT("Knight"));
						}
						break;
					case EPlayerJob::Archer:
						break;
					case EPlayerJob::Mage:
						break;
					}
				}
				break;
			}
		}
	}
	AMainPlayerController* Controller = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());


	m_MainHUD->ShowUI(Controller->m_ShowUI);
	
}