// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "MainPlayerController.h"
#include "PlayerAnim.h"
#include "StaticMeshAttributes.h"
#include "../Effect/HitCameraShake.h"
#include "../UEKR2GameModeBase.h"
#include "../UI/MainHud.h"
#include "../UI/CharacterHUD.h"
#include "../UI/HPBar.h"
#include "Engine/TextureRenderTarget2D.h"
#include "UEKR2/UEKR2GameInstance.h"
#include "UEKR2/Material/PhysicalMaterialBase.h"
#include "../Effect/GhostTrail.h"
#include "../Network/PacketStream.h"
#include "UEKR2/Network/NetworkManager.h"
#include "UEKR2/Network/NetworkSession.h"
#include "../UEKR2SaveGame.h"


/*
언리얼엔진4에서 생성자는 에디터에서 게임을 실행할 경우 에디터에 배치되는 그 순간 호출된다.
에디터에서 게임을 플레이할 때는 생성자가 호출이 안된다.
↕
패키징된 최종 게임 실행파일로 실행을 한다면 생성자가 게임내에 배치될 때 호출된다.
*/
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));
	m_HPBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBar"));
	m_Capture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Capture"));
	m_Trail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail"));
	

	
	// 부모 Component로 Mesh를 지정한다.
	m_Arm->SetupAttachment(GetMesh());
	m_Capture->SetupAttachment(GetMesh());
	m_HPBar->SetupAttachment(GetMesh());
	m_Trail->SetupAttachment(GetMesh());
	
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

	
	m_OnGhostTrail = false;
	m_GhostTrailTime = 0.3f;
	m_GhostTrailTimeAcc = 0.f;
}

// 게임이 시작될 때나 스폰될 때 호출되는 함수
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Animation 블루프린트를 얻을 수 있다.
	m_AnimInstance = Cast<UPlayerAnim>(GetMesh()->GetAnimInstance());
	m_HPBarWidget = Cast<UHPBar>(m_HPBar->GetWidget());

	m_HPBarWidget->SetDelegate<APlayerCharacter>(this,&APlayerCharacter::NameWidgetCallback);

	AUEKR2GameModeBase* GameMode = Cast<AUEKR2GameModeBase>(GetWorld()->GetAuthGameMode());
	if(IsValid(GameMode))
	{
		UMainHUD* MainHud = GameMode->GetMainHUD();

		if(IsValid(MainHud))
		{
			UCharacterHUD* CharacterHUD = MainHud->GetCharacterHUD();

			if(IsValid(CharacterHUD))
			{
				CharacterHUD->SetDelegate<APlayerCharacter>(this,&APlayerCharacter::CharacterNameWidgetCallback);
			}
		}
	}

	m_Capture->ShowOnlyActors.Add(this);
	
	LOGSTRING(TestString);

	// Save Data를 읽어온다.
/*
	UUEKR2SaveGame* LoadGame = Cast<UUEKR2SaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Save1"),0));
	if(LoadGame)
	{
		m_PlayerInfo = LoadGame->GetPlayerInfo();
		SetActorLocation(LoadGame->GetPos());
		SetActorScale3D(LoadGame->GetScale());
		Controller->SetControlRotation(LoadGame->GetRot());
	}
	*/

	FString FullPath = FString::Printf(TEXT("%s%s"),
		*FPaths::ProjectSavedDir(),TEXT("SavePlayer.txt"));

	TSharedPtr<FArchive> FileReader = MakeShareable(IFileManager::Get().CreateFileReader(*FullPath));

	*FileReader.Get()  << m_PlayerInfo.Name;
	*FileReader.Get()  << m_PlayerInfo.Armor;
	*FileReader.Get()  << m_PlayerInfo.Attack;
	*FileReader.Get()  << m_PlayerInfo.Exp;
	*FileReader.Get()  << m_PlayerInfo.Gold;
	*FileReader.Get()  << m_PlayerInfo.Job;
	*FileReader.Get()  << m_PlayerInfo.Level;
	*FileReader.Get()  << m_PlayerInfo.AttackAngle;
	*FileReader.Get()  << m_PlayerInfo.AttackDistance;
	*FileReader.Get()  << m_PlayerInfo.AttackSpeed;
	*FileReader.Get()  << m_PlayerInfo.HP;
	*FileReader.Get()  << m_PlayerInfo.HPMax;
	*FileReader.Get()  << m_PlayerInfo.MP;
	*FileReader.Get()  << m_PlayerInfo.MPMax;
	*FileReader.Get()  << m_PlayerInfo.MoveSpeed;
	FVector Pos, Scale;
	FRotator Rot;

	*FileReader.Get()<<Pos;
	*FileReader.Get()<<Scale;
	*FileReader.Get()<<Rot;

	SetActorLocation(Pos);
	Controller->SetControlRotation(Rot);
	SetActorScale3D(Scale);
	
	// 서버에 현재 캐릭터의  위치를 넘겨준다.
	NetworkSession* Session = NetworkManager::GetInst()->GetSession();

	PacketStream	stream;
	uint8 Packet[PACKET_SIZE]={};
	
	stream.SetBuffer(Packet);

	//FVector Loc=GetActorLocation();
	//FRotator Rot=GetActorRotation();
	//FVector Scale=GetActorScale();

	int32 Job = (int32)m_PlayerInfo.Job;
	
	stream.Write(&Job,sizeof(int32));
	stream.Write(&Pos,sizeof(FVector));
	stream.Write(&Scale,sizeof(FVector));
	stream.Write(&Rot,sizeof(FRotator));
	
	Session->Write((int)NetworkProtocol::UserConnect,stream.GetLength(),Packet);
	
}

// 매 프레임마다 호출
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
/*
	if(GetCharacterMovement()->Velocity.Size()>0.f)
	{
		m_Trail->SetEmitterEnable(TEXT("Trail"),true);
	}
	else
	{
		m_Trail->SetEmitterEnable(TEXT("Trail"),false);
	}*/
}

// 입력처리 때 호출
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("CameraZoom"), this, &APlayerCharacter::CameraZoomKey);
	PlayerInputComponent->BindAxis(TEXT("CameraLookUp"), this, &APlayerCharacter::CameraLookUpKey);
	PlayerInputComponent->BindAxis(TEXT("CameraRotation"), this, &APlayerCharacter::CameraRotationKey);
	PlayerInputComponent->BindAxis(TEXT("MoveFront"), this, &APlayerCharacter::MoveFrontKey);
	PlayerInputComponent->BindAxis(TEXT("MoveSide"), this, &APlayerCharacter::MoveSideKey);
	PlayerInputComponent->BindAxis(TEXT("RotationZ"), this, &APlayerCharacter::RotationZKey);

	//스페이스 바를 누를 때 점프
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed,this,&APlayerCharacter::JumpKey);

	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed,this,&APlayerCharacter::AttackKey);

	PlayerInputComponent->BindAction(TEXT("Skill1"), EInputEvent::IE_Pressed,this,&APlayerCharacter::Skill1Key);
	
	PlayerInputComponent->BindAction(TEXT("Skill2"), EInputEvent::IE_Pressed,this,&APlayerCharacter::Skill2Key);
	
	PlayerInputComponent->BindAction(TEXT("Skill3"), EInputEvent::IE_Pressed,this,&APlayerCharacter::Skill3Key);
	
	PlayerInputComponent->BindAction(TEXT("ShowUI"), EInputEvent::IE_Pressed,this,&APlayerCharacter::changeShowUI);
	
	PlayerInputComponent->BindAction(TEXT("Save"), EInputEvent::IE_Pressed,this,&APlayerCharacter::GameSaveKey);

}

void APlayerCharacter::MoveFrontKey(float Scale)
{
	if(!m_Casting)
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

void APlayerCharacter::MoveSideKey(float Scale)
{
	if(!m_Casting)
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
		if(m_MoveKey)
		{
			if(!m_OnGhostTrail)
			{
				m_GhostTrailTimeAcc = 0.f;
			}
			
			m_OnGhostTrail = true;
		}
		else if(GetCharacterMovement()->Velocity.Size()>0.f)
		{
			if(!m_OnGhostTrail)
			{
				m_GhostTrailTimeAcc = 0.f;
			}
			
			m_OnGhostTrail = true;
		}
		else
		{
			m_OnGhostTrail = false;
		}
	}
}





void APlayerCharacter::CameraZoomKey(float Scale)
{
	m_Arm->TargetArmLength -= Scale * 20.f;
	m_Arm->TargetOffset.Z-=Scale*20.f;
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
}

void APlayerCharacter::CameraLookUpKey(float Scale)
{
	FRotator Rot = m_Arm->GetRelativeRotation();

	Rot.Pitch += Scale * 10.f*GetWorld()->GetDeltaSeconds();

	if (Rot.Pitch > -15.f)
		Rot.Pitch = -15.f;

	if (Rot.Pitch < -45.f)
		Rot.Pitch = -45.f;
	m_Arm->SetRelativeRotation(Rot);

}

void APlayerCharacter::CameraRotationKey(float Scale)
{
	//FRotator Rot = m_Arm->GetRelativeRotation();
	//
	//Rot.Yaw += Scale * 100.f*GetWorld()->GetDeltaSeconds();
	//m_Arm->SetRelativeRotation(Rot);
	AddControllerYawInput(Scale);
}

void APlayerCharacter::JumpKey()
{


	if(!m_Casting)
	{
		if(m_Death)
			return;

		if(m_AnimInstance->GetAnimType()==EPlayerAnimType::Ground)
		{
			Jump();
			m_AnimInstance->ChangeAnimType(EPlayerAnimType::Jump);
		}
	}
}

void APlayerCharacter::RotationZKey(float Scale) {
	AddControllerYawInput(Scale*0.5f);
}
void APlayerCharacter::AttackKey() {
	if (m_AttackEnable)
	{
		m_AttackEnable = false;
		Attack();
	}
}
void APlayerCharacter::Skill1Key()
{
	if(m_Casting==true)
		return;
	
	m_AttackEnable = false;
	Skill1();
}

void APlayerCharacter::Skill2Key()
{
	if(m_Casting==true)
		return;
	m_AttackEnable = false;
	SetCasting(true);
	Skill2();
}

void APlayerCharacter::Skill3Key()
{
	if(m_Casting==true)
		return;
	m_AttackEnable = false;
	SetCasting(true);
	Skill3();
}

void APlayerCharacter::GameSaveKey()
{
	/*
	// 언리얼에서 지원하는 세이브 방식
	UUEKR2SaveGame* SaveGame = NewObject<UUEKR2SaveGame>();

	SaveGame->SetPlayerInfo(m_PlayerInfo);
	SaveGame->SetPos(GetActorLocation());
	SaveGame->SetRot(GetActorRotation());
	SaveGame->SetScale(GetActorScale());

	UGameplayStatics::SaveGameToSlot(SaveGame, "Save1",0);
	*/
	FString FullPath = FString::Printf(TEXT("%s%s"),
		*FPaths::ProjectSavedDir(),TEXT("SavePlayer.txt"));

	FArchive* Writer =  IFileManager::Get().CreateFileWriter(*FullPath);

	if(Writer)
	{
		*Writer << m_PlayerInfo.Name;
		*Writer << m_PlayerInfo.Armor;
		*Writer << m_PlayerInfo.Attack;
		*Writer << m_PlayerInfo.Exp;
		*Writer << m_PlayerInfo.Gold;
		*Writer << m_PlayerInfo.Job;
		*Writer << m_PlayerInfo.Level;
		*Writer << m_PlayerInfo.AttackAngle;
		*Writer << m_PlayerInfo.AttackDistance;
		*Writer << m_PlayerInfo.AttackSpeed;
		*Writer << m_PlayerInfo.HP;
		*Writer << m_PlayerInfo.HPMax;
		*Writer << m_PlayerInfo.MP;
		*Writer << m_PlayerInfo.MPMax;
		*Writer << m_PlayerInfo.MoveSpeed;

		FVector Pos, Scale;
		Pos = GetActorLocation();
		Scale = GetActorScale();
		FRotator Rot = GetActorRotation();
		
		*Writer <<Pos;
		*Writer <<Scale;
		*Writer <<Rot;

		Writer->Close();

		delete Writer;
	}
}


void APlayerCharacter::changeShowUI()
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


void APlayerCharacter::PlayFallRecovery()
{
	if(!m_FallRecoveryMontage)
		return;

	if(!m_AnimInstance->Montage_IsPlaying(m_FallRecoveryMontage))
	{
		m_AnimInstance->Montage_SetPosition(m_FallRecoveryMontage,0.f);

		m_AnimInstance->Montage_Play(m_FallRecoveryMontage);
	}
}




void APlayerCharacter::Attack() {

}
void APlayerCharacter::Skill1() {

}

void APlayerCharacter::Skill2() {

}
void APlayerCharacter::Skill3() {

}

void APlayerCharacter::AttackCombo() {

}

void APlayerCharacter::NormalAttack() {

}

void APlayerCharacter::AttackEnd() {
	m_AttackEnable = true;
	m_Attack=false;
}

void APlayerCharacter::UseSkill(int32 Index)
{
}

void APlayerCharacter::UseSkillFire(int32 Index)
{
}

void APlayerCharacter::GhostTrailEnd()
{
	m_OnGhostTrail =false;
	m_GhostTrailTimeAcc=0.f;
}

void APlayerCharacter::OnGhostTrail()
{
	
	m_OnGhostTrail =true;
	m_GhostTrailTimeAcc=0.f;
}

float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
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
	AUEKR2GameModeBase* GameMode = Cast<AUEKR2GameModeBase>(GetWorld()->GetAuthGameMode());
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

void APlayerCharacter::NameWidgetCallback()
{
	m_HPBarWidget->SetName(m_PlayerInfo.Name);
}

void APlayerCharacter::CharacterNameWidgetCallback()
{
	AUEKR2GameModeBase* GameMode = Cast<AUEKR2GameModeBase>(GetWorld()->GetAuthGameMode());
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

void APlayerCharacter::FootStep(bool Left)
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
