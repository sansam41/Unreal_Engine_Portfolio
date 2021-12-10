// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "../UEKR2GameInstance.h"
#include "MonsterAIController.h"
#include "MonsterSpawnPoint.h"
#include "../Effect/HitCameraShake.h"
#include "../UI/HPBar.h"
#include "PatrolPointSpline.h"
#include "UEKR2/Item/ItemBox.h"
#include "../UEKR2GameModeBase.h"
#include "UEKR2/RPG/RPGGameModeBase.h"

// Sets default values
AMonster::AMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_SpawnPoint = nullptr;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	m_HPBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBar"));

	m_HPBar->SetupAttachment(GetMesh());

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetCharacterMovement()->MaxWalkSpeed = 400.f;

	m_AttackEnd = false;
	m_PatrolIndex = 1;
	SetCanBeDamaged(true);



	static ConstructorHelpers::FClassFinder<UUserWidget>	HPBarAsset(TEXT("WidgetBlueprint'/Game/UI/UI_HPBar.UI_HPBar_C'"));

	if (HPBarAsset.Succeeded())
		m_HPBar->SetWidgetClass(HPBarAsset.Class);

	m_HPBar->SetWidgetSpace(EWidgetSpace::Screen);
	m_HPBar->SetDrawSize(FVector2D(200.f, 60.f));
	m_HPBar->SetRelativeLocation(FVector(0.f, 0.f, 230.f));
	m_HPBar->SetBlendMode(EWidgetBlendMode::Transparent);
	
	GetMesh()->bReceivesDecals = false;

	m_Dissolve = 1.5f;
	m_DissolveTime = 5.f;
	m_DissolveAccTime = 0.f;
	m_DissolveEnable = false;
	m_DissolveMin = 0.f;
	m_DissolveMax = 1.f;

	m_DissolveRange = m_DissolveMax - m_DissolveMin;

	m_PatrolSpline = nullptr;

	m_PatrolEnable = false;
	m_PatrolLength = 0.f;
	m_CurrentPatrolLength = 0.f;
	m_CurrentPatrolIndex = 0;

	IsDead=false;
	m_Boss = false;
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	
	UUEKR2GameInstance* GameInst = Cast<UUEKR2GameInstance>(GetWorld()->GetGameInstance());

	if (GameInst)
	{
		const FMonsterTableInfo* Info = GameInst->FindMonsterInfo(m_MonsterInfoName);

		if (Info)
		{
			m_MonsterInfo.Name = Info->Name;
			m_MonsterInfo.Attack = Info->Attack;
			m_MonsterInfo.Armor = Info->Armor;
			m_MonsterInfo.HP = Info->HP;
			m_MonsterInfo.HPMax = Info->HPMax;
			m_MonsterInfo.MP = Info->MP;
			m_MonsterInfo.MPMax = Info->MPMax;
			m_MonsterInfo.Level = Info->Level;
			m_MonsterInfo.Exp = Info->Exp;
			m_MonsterInfo.Gold = Info->Gold;
			m_MonsterInfo.AttackDistance = Info->AttackDistance;
			m_MonsterInfo.AttackSpeed = Info->AttackSpeed;
			m_MonsterInfo.AttackAngle = Info->AttackAngle;
			m_MonsterInfo.MoveSpeed = Info->MoveSpeed;
			m_MonsterInfo.TraceDistance = Info->TraceDistance;
		}

	}

	m_AnimInstance = Cast<UMonsterAnimInstance>(GetMesh()->GetAnimInstance());

	m_HPBarWidget = Cast<UHPBar>(m_HPBar->GetWidget());
	m_HPBarWidget->SetVisibility(ESlateVisibility::Collapsed);

	m_HPBarWidget->SetDelegate<AMonster>(this, &AMonster::NameWidgetCallback);

	//m_HPBarWidget->SetName(m_MonsterInfo.Name);

	GetMesh()->SetScalarParameterValueOnMaterials(TEXT("DissolveEnable"), -1.f);

	m_DissolveRange = m_DissolveMax - m_DissolveMin;
	m_Dissolve = m_DissolveMax;
}

void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_PatrolEnable)
	{
		m_CurrentPatrolLength += GetCharacterMovement()->MaxWalkSpeed * DeltaTime;

		if (m_CurrentPatrolLength >= m_PatrolSpline->GetSplineLength())
		{
			m_CurrentPatrolLength -= m_PatrolSpline->GetSplineLength();
		}
	}

	if (m_DissolveEnable)
	{
		m_DissolveAccTime += DeltaTime;

		m_Dissolve = m_DissolveMax - (m_DissolveAccTime / m_DissolveTime * m_DissolveRange);

		GetMesh()->SetScalarParameterValueOnMaterials(TEXT("Appearance"), m_Dissolve);

		if (m_DissolveAccTime >= m_DissolveTime)
		{
			m_DissolveAccTime = m_DissolveTime;

			m_Dissolve = m_DissolveMin;

			if(m_SpawnPoint)
				m_SpawnPoint->Death();
			Destroy();
		}
	}
}

bool AMonster::GetPatrolWait()
{
	return m_PatrolSpline->GetSplineLength() / 3.f * (m_CurrentPatrolIndex + 1) <= m_CurrentPatrolLength;
}

FVector AMonster::GetPatrolPointSpline()
{
	return m_PatrolSpline->GetSplinePoint(m_CurrentPatrolLength);
}

EMonsterAnimType AMonster::GetAnimType()	const
{
	return m_AnimInstance->GetAnimType();
}

void AMonster::ChangeAnimType(EMonsterAnimType Type)
{
	m_AnimInstance->ChangeAnimType(Type);
}
EMonsterAttackType AMonster::GetAttackType()	const
{
	return m_AnimInstance->GetAttackType();
}
void AMonster::ChangeAttackType(EMonsterAttackType Type)
{
	m_AnimInstance->ChangeAttackType(Type);
}

float AMonster::TakeDamage(float DamageAmount, 
	struct FDamageEvent const& DamageEvent, 
	class AController* EventInstigator, AActor* DamageCauser)
{
	if(m_HPBarWidget->GetVisibility()!=ESlateVisibility::Visible)
		m_HPBarWidget->SetVisibility(ESlateVisibility::Visible);
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (Damage == 0.f)
		return 0.f;

	Damage = Damage - m_MonsterInfo.Armor;
	Damage = Damage < 1.f ? 1.f : Damage;

	m_MonsterInfo.HP -= Damage;

	// 몬스터가 죽었을 경우
	if (m_MonsterInfo.HP <= 0)
	{
		m_AnimInstance->ChangeAnimType(EMonsterAnimType::Death);

		AMonsterAIController* MonsterController = Cast<AMonsterAIController>(GetController());
		IsDead=true;
		if (MonsterController)
		{
			MonsterController->StopMovement();
			MonsterController->BrainComponent->StopLogic(TEXT("Dead"));
		}
		// 몬스터가 죽었을 경우 퀘스트 체크
		ARPGGameModeBase* GameMode = Cast<ARPGGameModeBase>(GetWorld()->GetAuthGameMode());
		if(GameMode)
		{
			UQuestWidget* QuestWidget = GameMode->GetMainHUD()->GetQuestWidget();

			if(QuestWidget)
			{
				QuestWidget->QuestCheck(EQuestType::Hunt,m_MonsterInfo.Name);
				PrintViewport(1.f,FColor::Red,m_MonsterInfo.Name);
			}
		}

		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);


		// 몬스터의 아이템 드랍률
		float Percent = FMath::RandRange(0.f, 100.f);
		if (Percent <= 50.f)
		{
			// 각 아이템 드랍률
			//Percent = FMath::RandRange(0.f, 100.f);
			int32 Index = FMath::RandRange(0,m_DropItemNameArray.Num()-1);

			UUEKR2GameInstance* GameInst = Cast<UUEKR2GameInstance>(GetWorld()->GetGameInstance());

			if(GameInst)
			{
				const FUIItemTableInfo* ItemInfo = GameInst->FindUIItemInfo(m_DropItemNameArray[Index]);
				if(ItemInfo)
				{
					FActorSpawnParameters	param;
					param.SpawnCollisionHandlingOverride =
						ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

					FBox SpawnBox(GetMesh()->GetComponentLocation()-FVector(50.f,50.f,-150.f),
						GetMesh()->GetComponentLocation()+FVector(50.f,50.f,200.f));

					// 아이템 상자를 생성한다.
					AItemBox* ItemBox = GetWorld()->SpawnActor<AItemBox>(AItemBox::StaticClass(),
						FMath::RandPointInBox(SpawnBox),
						GetMesh()->GetComponentRotation(),param);

					if(ItemBox)
					{
						ItemBox->SetMesh(ItemInfo->Mesh);
					
						ItemBox->SetItemName(m_DropItemNameArray[Index]);
					}
				}
			}
		}
	}

	else
		m_AnimInstance->SetHit();

	if (IsValid(m_HPBarWidget))
	{
		m_HPBarWidget->SetHPPercent(m_MonsterInfo.HP / (float)m_MonsterInfo.HPMax);
	}

	return Damage;
}

void AMonster::Death()
{
	// 죽었을때 처리할 내용을 처리한다.
	// 죽었을때의 효과나 아이템 생성 등을 처리한다.
	// 객체를 제거한다.
	//Destroy();

	GetMesh()->SetScalarParameterValueOnMaterials(TEXT("DissolveEnable"), 1.f);


	GetCharacterMovement()->Velocity = FVector::ZeroVector;
	m_DissolveEnable = true;
}

void AMonster::NormalAttack()
{
}

void AMonster::NameWidgetCallback()
{
	m_HPBarWidget->SetName(m_MonsterInfo.Name);
}
