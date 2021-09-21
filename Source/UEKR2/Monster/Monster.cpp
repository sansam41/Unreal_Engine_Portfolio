// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "MonsterAIController.h"
#include "MonsterSpawnPoint.h"
#include "../UEKR2GameInstance.h"
#include "../UI/HPBar.h"
// Sets default values
AMonster::AMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_SpawnPoint = nullptr;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	m_AttackEnd = false;
	m_PatrolIndex=1;

	SetCanBeDamaged(true);

	m_HPBar=CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBar"));

	m_HPBar->SetupAttachment(GetMesh());

	ConstructorHelpers::FClassFinder<UUserWidget> HPBarAsset(TEXT("WidgetBlueprint'/Game/UI/UI_HPBar.UI_HPBar_C'"));
	if(HPBarAsset.Succeeded())
		m_HPBar->SetWidgetClass(HPBarAsset.Class);

	m_HPBar->SetWidgetSpace(EWidgetSpace::Screen);
	m_HPBar->SetDrawSize(FVector2D(200.f,60.f));
	m_HPBar->SetRelativeLocation(FVector(0,0,230.f));
	m_HPBar->SetBlendMode(EWidgetBlendMode::Transparent);

	GetMesh()->bReceivesDecals=false;
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();

	UUEKR2GameInstance* GameInst = Cast<UUEKR2GameInstance>(GetWorld()->GetGameInstance());

	if (GameInst) 
	{
		const FMonsterTableInfo* Info = GameInst->FindMonsterInfo(m_MonsterInfoName);

		if(Info)
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
			m_MonsterInfo.AttackAngle = Info->AttackAngle;
			m_MonsterInfo.AttackDistance = Info->AttackDistance;
			m_MonsterInfo.AttackSpeed = Info->AttackSpeed;
			m_MonsterInfo.MoveSpeed = Info->MoveSpeed;
			m_MonsterInfo.TraceDistance = Info->TraceDistance;
		}
	}

	m_AnimInstance = Cast<UMonsterAnimInstance>(GetMesh()->GetAnimInstance());
	
	m_HPBarWidget = Cast<UHPBar>(m_HPBar->GetWidget());

	m_HPBarWidget->SetDelegate<AMonster>(this,&AMonster::NameWidgetCallback);
	
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


EMonsterAnimType AMonster::GetAnimType() const
{
	return m_AnimInstance->GetAnimType();
}

void AMonster::ChangeAnimType(EMonsterAnimType Type)
{
	m_AnimInstance->ChangeAnimType(Type);
}

float AMonster::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if(Damage ==0.f)
		return 0.f;
	Damage = Damage - m_MonsterInfo.Armor;

	Damage = Damage <1.f ? 1.f:Damage;

	m_MonsterInfo.HP-=Damage;

	// 몬스터가 죽었을 경우
	if(m_MonsterInfo.HP<=0)
	{
		m_AnimInstance->ChangeAnimType(EMonsterAnimType::Death);
		AMonsterAIController* MonsterController = Cast<AMonsterAIController>(GetController());

		if(MonsterController)
		{
			this->GetCharacterMovement()->MaxWalkSpeed = 0.f;
			MonsterController->BrainComponent->StopLogic(TEXT("Dead"));
		}
	}
	else
	{
		m_AnimInstance->SetHit();
	}


	if (IsValid(m_HPBarWidget))
	{
		m_HPBarWidget->SetHPPercent(m_MonsterInfo.HP / (float)m_MonsterInfo.HPMax);
	}
	
	return Damage;
}

void AMonster::Death()
{
	// 죽었을 때 처리할 내용을 구현
	// 죽었을 때의 효과나 아이템 생성 등을 처리한다.
	Destroy();
	m_SpawnPoint->Death();
}

void AMonster::NormalAttack()
{
	
}

void AMonster::NameWidgetCallback()
{
	m_HPBarWidget->SetName(m_MonsterInfo.Name);
}


