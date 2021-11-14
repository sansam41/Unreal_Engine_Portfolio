// Fill out your copyright notice in the Description page of Project Settings.


#include "RPG_PlayerCharacter.h"

#include "UEKR2/Player/MainPlayerController.h"
#include "RPGPlayerAnim.h"
#include "StaticMeshAttributes.h"
#include "UEKR2//Effect/HitCameraShake.h"
#include "UEKR2//UI/MainHud.h"
#include "UEKR2//UI/CharacterHUD.h"
#include "UEKR2//UI/HPBar.h"
#include "Engine/TextureRenderTarget2D.h"
#include "UEKR2/UEKR2GameInstance.h"
#include "UEKR2/Material/PhysicalMaterialBase.h"
#include "UEKR2//Effect/GhostTrail.h"
#include "UEKR2//Network/PacketStream.h"
#include "UEKR2/Network/NetworkManager.h"
#include "UEKR2/Network/NetworkSession.h"
#include "UEKR2/RPG/RPGGameModeBase.h"


/*
언리얼엔진4에서 생성자는 에디터에서 게임을 실행할 경우 에디터에 배치되는 그 순간 호출된다.
에디터에서 게임을 플레이할 때는 생성자가 호출이 안된다.
↕
패키징된 최종 게임 실행파일로 실행을 한다면 생성자가 게임내에 배치될 때 호출된다.
*/
ARPG_PlayerCharacter::ARPG_PlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));
	m_HPBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBar"));
	m_Capture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Capture"));
	

	
	// 부모 Component로 Mesh를 지정한다.
	m_Arm->SetupAttachment(GetMesh());
	m_Capture->SetupAttachment(GetMesh());
	m_HPBar->SetupAttachment(GetMesh());
	
	// Camera의 부모 Component로 m_Arm를 지정한다.
	m_Camera->SetupAttachment(m_Arm);


	GetCharacterMovement()->JumpZVelocity = 600.f;

	m_MoveKey = false;
	m_AttackEnable = true;
	m_Death=false;
	m_Casting=false;
	m_ShowUI=false;
	
	

	
	m_FallRecoveryMontage = nullptr;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));

	GetMesh()->SetReceivesDecals(false);

	
	SetCanBeDamaged(true);

	static ConstructorHelpers::FClassFinder<UUserWidget> HPBarAsset(TEXT("WidgetBlueprint'/Game/UI/UI_HPBar.UI_HPBar_C'"));
	if(HPBarAsset.Succeeded())
		m_HPBar->SetWidgetClass(HPBarAsset.Class);

	m_HPBar->SetWidgetSpace(EWidgetSpace::Screen);
	m_HPBar->SetDrawSize(FVector2D(200.f,60.f));
	m_HPBar->SetRelativeLocation(FVector(0,0,230.f));
	m_HPBar->SetBlendMode(EWidgetBlendMode::Transparent);

	static ConstructorHelpers::FObjectFinder<UTextureRenderTarget2D> FaceTargetObj(TEXT("TextureRenderTarget2D'/Game/Player/RTPlayerFace.RTPlayerFace'"));
	if(FaceTargetObj.Succeeded())
		m_FaceTarget=FaceTargetObj.Object;
	
	m_Capture->PrimitiveRenderMode = ESceneCapturePrimitiveRenderMode::PRM_UseShowOnlyList;
	m_Capture->CaptureSource= ESceneCaptureSource::SCS_SceneColorSceneDepth;

	m_Capture->TextureTarget = m_FaceTarget;
	m_Capture->SetRelativeLocation(FVector(0.f,80.f,170.f));
	m_Capture->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
	
	m_PlayerMesh = nullptr;
	GetCharacterMovement()->JumpZVelocity = 500.f;
	
}

// 게임이 시작될 때나 스폰될 때 호출되는 함수
void ARPG_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Animation 블루프린트를 얻을 수 있다.
	m_AnimInstance = Cast<URPGPlayerAnim>(GetMesh()->GetAnimInstance());
	m_HPBarWidget = Cast<UHPBar>(m_HPBar->GetWidget());

	m_HPBarWidget->SetDelegate<ARPG_PlayerCharacter>(this,&ARPG_PlayerCharacter::NameWidgetCallback);

	ARPGGameModeBase* GameMode = Cast<ARPGGameModeBase>(GetWorld()->GetAuthGameMode());
	if(IsValid(GameMode))
	{
		UMainHUD* MainHud = GameMode->GetMainHUD();

		if(IsValid(MainHud))
		{
			UCharacterHUD* CharacterHUD = MainHud->GetCharacterHUD();

			if(IsValid(CharacterHUD))
			{
				CharacterHUD->SetDelegate<ARPG_PlayerCharacter>(this,&ARPG_PlayerCharacter::CharacterNameWidgetCallback);
			}
		}
	}

	m_Capture->ShowOnlyActors.Add(this);
	
	LOGSTRING(TestString);

	// 서버에 현재 캐릭터의  위치를 넘겨준다.
	NetworkSession* Session = NetworkManager::GetInst()->GetSession();

	PacketStream	stream;
	uint8 Packet[PACKET_SIZE]={};
	
	stream.SetBuffer(Packet);

	FVector Loc=GetActorLocation();
	FRotator Rot=GetActorRotation();
	FVector Scale=GetActorScale();

	int32 Job = (int32)m_PlayerInfo.Job;
	
	stream.Write(&Job,sizeof(int32));
	stream.Write(&Loc,sizeof(FVector));
	stream.Write(&Scale,sizeof(FVector));
	stream.Write(&Rot,sizeof(FRotator));
	
	Session->Write((int)NetworkProtocol::UserConnect,stream.GetLength(),Packet);
	
	GameMode = Cast<ARPGGameModeBase>(GetWorld()->GetAuthGameMode());

	if(GameMode)
	{
		UMinimapWidget* Minimap = GameMode ->GetMainHUD()->GetMinimapWidget();

		if(Minimap)
		{
			Minimap->RotationArrow(Rot.Yaw);
		}
	}

	GetWorldTimerManager().SetTimer(m_MonsterDetectTimer,
		this, &ARPG_PlayerCharacter::MonsterDetect, 0.03f, true);
	
}

// 매 프레임마다 호출
void ARPG_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// 입력처리 때 호출
void ARPG_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("CameraZoom"), this, &ARPG_PlayerCharacter::CameraZoomKey);
	PlayerInputComponent->BindAxis(TEXT("CameraLookUp"), this, &ARPG_PlayerCharacter::CameraLookUpKey);
	PlayerInputComponent->BindAxis(TEXT("CameraRotation"), this, &ARPG_PlayerCharacter::CameraRotationKey);
	PlayerInputComponent->BindAxis(TEXT("MoveFront"), this, &ARPG_PlayerCharacter::MoveFrontKey);
	PlayerInputComponent->BindAxis(TEXT("MoveSide"), this, &ARPG_PlayerCharacter::MoveSideKey);
	PlayerInputComponent->BindAxis(TEXT("RotationZ"), this, &ARPG_PlayerCharacter::RotationZKey);

	//스페이스 바를 누를 때 점프
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed,this,&ARPG_PlayerCharacter::JumpKey);

	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed,this,&ARPG_PlayerCharacter::AttackKey);

	PlayerInputComponent->BindAction(TEXT("Skill1"), EInputEvent::IE_Pressed,this,&ARPG_PlayerCharacter::Skill1Key);
	
	PlayerInputComponent->BindAction(TEXT("Skill2"), EInputEvent::IE_Pressed,this,&ARPG_PlayerCharacter::Skill2Key);
	
	PlayerInputComponent->BindAction(TEXT("Skill3"), EInputEvent::IE_Pressed,this,&ARPG_PlayerCharacter::Skill3Key);
	
	PlayerInputComponent->BindAction(TEXT("ShowUI"), EInputEvent::IE_Pressed,this,&ARPG_PlayerCharacter::changeShowUI);

}

void ARPG_PlayerCharacter::MoveFrontKey(float Scale)
{
	if(!m_Casting&&!m_Attack)
	{
		AddMovementInput(GetActorForwardVector(), Scale);
		
		if (Scale == 0.f) {
			m_MoveKey = false;
			m_AnimInstance->SetDirection(0.f);
		}
		else if (Scale == 1.f)
		{
			m_MoveKey = true;
			m_AnimInstance->SetDirection(0.f);
			
		}
		else
		{
			m_MoveKey = true;
			m_AnimInstance->SetDirection(180.f);
		}
	}
}

void ARPG_PlayerCharacter::MoveSideKey(float Scale)
{
	if(!m_Casting&&!m_Attack)
	{
		AddMovementInput(GetActorRightVector(), Scale);

		float Direction = m_AnimInstance->GetDirection();

		if (Scale == 1.f)
		{
			m_MoveKey = true;
			if (Direction == 0.f) {
				m_AnimInstance->SetDirection(45.f);
			}
			else
				m_AnimInstance->SetDirection(135.f);
		}
		else if (Scale == -1.f)
		{
			m_MoveKey = true;
			if (Direction == 0.f) {
				m_AnimInstance->SetDirection(-45.f);
			}
			else
				m_AnimInstance->SetDirection(-135.f);
		}
	}
}





void ARPG_PlayerCharacter::CameraZoomKey(float Scale)
{
	m_Arm->TargetArmLength -= Scale * 30.f;
	m_Arm->TargetOffset.Z-=Scale*30.f;
	if (m_Arm->TargetArmLength < 200.f)
	{
		m_Arm->TargetArmLength = 200.f;
		m_Arm->TargetOffset.Z = 200.f;
	}
	if (m_Arm->TargetArmLength > 500.f)
	{
		m_Arm->TargetArmLength = 500.f;
		m_Arm->TargetOffset.Z = 500.f;
	}
	FRotator Rot = m_Arm->GetRelativeRotation();

	Rot.Pitch += Scale * 3.f;

	if (Rot.Pitch > -15.f)
	{
		Rot.Pitch = -15.f;
	}
	if (Rot.Pitch < -45.f)
	{
		Rot.Pitch = -45.f;
	}
	m_Arm->SetRelativeRotation(Rot);
}

void ARPG_PlayerCharacter::CameraLookUpKey(float Scale)
{


}

void ARPG_PlayerCharacter::CameraRotationKey(float Scale)
{
	//FRotator Rot = m_Arm->GetRelativeRotation();
	//
	//Rot.Yaw += Scale * 100.f*GetWorld()->GetDeltaSeconds();
	//m_Arm->SetRelativeRotation(Rot);
	AddControllerYawInput(Scale);

	if(Scale!=0.f)
	{
		ARPGGameModeBase* GameMode = Cast<ARPGGameModeBase>(GetWorld()->GetAuthGameMode());

		if(GameMode)
		{
			UMinimapWidget* Minimap = GameMode ->GetMainHUD()->GetMinimapWidget();
			if(Minimap)
			{
				Minimap->RotationArrow(GetActorRotation().Yaw);
			}
		}
	}
}

void ARPG_PlayerCharacter::JumpKey()
{


	if(!m_Casting)
	{
		if(m_Death)
			return;

		if(m_AnimInstance->GetAnimType()==ERPG_PlayerAnimType::Ground)
		{
			Jump();
			m_AnimInstance->ChangeAnimType(ERPG_PlayerAnimType::Jump);
		}
	}
}

void ARPG_PlayerCharacter::RotationZKey(float Scale) {
	AddControllerYawInput(Scale*0.5f);
}
void ARPG_PlayerCharacter::AttackKey() {
	if (m_AttackEnable)
	{
		PrintViewport(1.f, FColor::Yellow, TEXT("Attack"));
		m_Attack=true;
		m_AttackEnable = false;
		Attack();
	}
	else
		return;
}
void ARPG_PlayerCharacter::Skill1Key()
{
	if(m_Casting==true)
		return;
	
	m_AttackEnable = false;
	Skill1();
}

void ARPG_PlayerCharacter::Skill2Key()
{
	if(m_Casting==true)
		return;
	m_AttackEnable = false;
	SetCasting(true);
	Skill2();
}

void ARPG_PlayerCharacter::Skill3Key()
{
	if(m_Casting==true)
		return;
	m_AttackEnable = false;
	SetCasting(true);
	Skill3();
}


void ARPG_PlayerCharacter::changeShowUI()
{
	
	AMainPlayerController* PlayerController=Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
	if(m_ShowUI)
	{
		m_ShowUI=false;
			
		PlayerController->bShowMouseCursor = false;
		PlayerController->m_ShowUI=false;
	}
	else
	{	m_ShowUI=true;
			
		PlayerController->bShowMouseCursor = true;
		PlayerController->m_ShowUI=true;
	}
}




void ARPG_PlayerCharacter::Attack() {
	

}
void ARPG_PlayerCharacter::Skill1() {

}

void ARPG_PlayerCharacter::Skill2() {

}
void ARPG_PlayerCharacter::Skill3() {

}


void ARPG_PlayerCharacter::NormalAttack() {

}

void ARPG_PlayerCharacter::AttackEnd() {
	m_AttackEnable = true;
	m_Attack=false;
}

void ARPG_PlayerCharacter::UseSkill(int32 Index)
{
}

void ARPG_PlayerCharacter::UseSkillFire(int32 Index)
{
}


float ARPG_PlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if(Damage ==0.f)
		return 0.f;
	Damage = Damage - m_PlayerInfo.Armor;

	Damage = Damage <1.f ? 1.f:Damage;

	m_PlayerInfo.HP-=Damage;

	// 플레이어가 죽었을 경우
	if (m_PlayerInfo.HP <= 0)
	{
		//m_AnimInstance->ChangeAnimType(EMonsterAnimType::Death);

		//AMonsterAIController* MonsterController = Cast<AMonsterAIController>(GetController());

		//if (MonsterController)
		//	MonsterController->BrainComponent->StopLogic(TEXT("Dead"));
	}
	ARPGGameModeBase* GameMode = Cast<ARPGGameModeBase>(GetWorld()->GetAuthGameMode());
	if(IsValid(GameMode))
	{
		UMainHUD* MainHud = GameMode->GetMainHUD();

		if(IsValid(MainHud))
		{
			UCharacterHUD* CharacterHUD = MainHud->GetCharacterHUD();

			if(IsValid(CharacterHUD))
			{
				CharacterHUD->SetHPPercent(m_PlayerInfo.HP/(float)m_PlayerInfo.HPMax);
			}
		}
	}
	
	if (IsValid(m_HPBarWidget))
	{
		m_HPBarWidget->SetHPPercent(m_PlayerInfo.HP / (float)m_PlayerInfo.HPMax);
	}

	GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(
		UHitCameraShake::StaticClass());

	
	return Damage;
}

void ARPG_PlayerCharacter::NameWidgetCallback()
{
	m_HPBarWidget->SetName(m_PlayerInfo.Name);
}

void ARPG_PlayerCharacter::CharacterNameWidgetCallback()
{
	ARPGGameModeBase* GameMode = Cast<ARPGGameModeBase>(GetWorld()->GetAuthGameMode());
	if(IsValid(GameMode))
	{
		UMainHUD* MainHud = GameMode->GetMainHUD();

		if(IsValid(MainHud))
		{
			UCharacterHUD* CharacterHUD = MainHud->GetCharacterHUD();

			if(IsValid(CharacterHUD))
			{
				CharacterHUD->SetName(m_PlayerInfo.Name);
			}
		}
	}

}

void ARPG_PlayerCharacter::FootStep(bool Left)
{
	FVector SocketLoc;
	if(Left)
		SocketLoc=GetMesh()->GetSocketLocation(TEXT("Foot_L"));
	else
		SocketLoc=GetMesh()->GetSocketLocation(TEXT("Foot_R"));

	// 소켓 위치에서 아래로 라인충돌
	FCollisionQueryParams params(NAME_None,false,this);

	params.bReturnPhysicalMaterial=true;
	FHitResult result;
	bool Hit = GetWorld()->LineTraceSingleByChannel(result,SocketLoc,SocketLoc+FVector(0.f,0.f,-100.f),
		ECollisionChannel::ECC_GameTraceChannel5,params);
	if(Hit)
	{
		UPhysicalMaterialBase* Phys=Cast<UPhysicalMaterialBase>(result.PhysMaterial);

		if (Phys)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), Phys->GetSound(), result.ImpactPoint);
		}
	}
	
}


// 미니맵에 표시하기 위함.
void ARPG_PlayerCharacter::MonsterDetect()
{
	TArray<FHitResult> resultArray;
	FVector Pos = GetActorLocation();
	FVector Start = Pos - FVector(1500.f,2000.f,1000.f);
	FVector End = Start + FVector(3000.f, 4000.f, 2000.f);
	FCollisionQueryParams	param(NAME_None,false,this);
	
	bool Collision = GetWorld()->SweepMultiByChannel(resultArray,
		Pos, Pos, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel11,
		FCollisionShape::MakeBox(FVector(1500.f, 2000.f, 1000.f)),
		param);
	
	ARPGGameModeBase* GameMode = Cast<ARPGGameModeBase>(GetWorld()->GetAuthGameMode());
	UMinimapWidget* Minimap = nullptr;

	if (GameMode)
	{
		Minimap = GameMode->GetMainHUD()->GetMinimapWidget();
	}

	if (Minimap)
		Minimap->ClearMonster();

	if (Collision)
	{
		for (auto& result : resultArray)
		{
			FVector	RelativePos = result.GetActor()->GetActorLocation() -
				Pos;

			// 1. X와 Y의 좌표가 UI에 맞춰서 변경되어야 한다.
			// 2. UI는 Y값이 위에서 0으로 시작하여 아래로 +값이
			// 된다.
			// 3. 가로, 세로의 배율은 10배로 잡혀있다.
			/*RelativePos *= 0.1f;

			RelativePos.X += 200.f;
			RelativePos.Y += 150.f;*/

			if (Minimap)
			{
				Minimap->AddMonster(RelativePos);
			}
		}
	}
}