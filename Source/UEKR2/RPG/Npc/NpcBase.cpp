// Fill out your copyright notice in the Description page of Project Settings.


#include "../../RPG/Npc/NpcBase.h"

#include "Kismet/KismetMathLibrary.h"
#include "UEKR2/RPG/RPGGameModeBase.h"
#include "UEKR2/UI/NpcDialogue.h"
#include "UEKR2/UI/NpcInfoBar.h"

// Sets default values
ANpcBase::ANpcBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	m_NpcInfoBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("NpcInfoBar"));
	m_Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));
	
	m_NpcInfoBar->SetupAttachment(GetMesh());
	m_Trigger->SetupAttachment(GetMesh());

	static ConstructorHelpers::FClassFinder<UUserWidget>	m_NpcInfoBarAsset(TEXT("WidgetBlueprint'/Game/UI/UI_NpcInfoBar.UI_NpcInfoBar_C'"));

	if (m_NpcInfoBarAsset.Succeeded())
		m_NpcInfoBar->SetWidgetClass(m_NpcInfoBarAsset.Class);

	m_NpcInfoBar->SetWidgetSpace(EWidgetSpace::Screen);
	m_NpcInfoBar->SetDrawSize(FVector2D(200.f, 60.f));
	m_NpcInfoBar->SetRelativeLocation(FVector(0.f, 0.f, 230.f));
	m_NpcInfoBar->SetBlendMode(EWidgetBlendMode::Transparent);

	
	Player=nullptr;



}

// Called when the game starts or when spawned
void ANpcBase::BeginPlay()
{
	Super::BeginPlay();

		

	
	
	m_NpcInfoBarWidget = Cast<UNpcInfoBar>(m_NpcInfoBar->GetWidget());
	m_NpcInfoBarWidget->SetDelegate<ANpcBase>(this, &ANpcBase::NameWidgetCallback);
	
	m_Trigger->OnComponentBeginOverlap.AddDynamic(this,&ANpcBase::TriggerBeginOverlap);
	m_Trigger->OnComponentEndOverlap.AddDynamic(this,&ANpcBase::TriggerEndOverlap);
}

// Called every frame
void ANpcBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(Player)
	{
		FVector Loc = GetActorLocation();
		FVector PlayerLoc = Player->GetActorLocation();
		
		FRotator rot = UKismetMathLibrary::FindLookAtRotation(Loc,PlayerLoc);
		SetActorRotation(FMath::Lerp(GetActorRotation(),rot,0.05f));
	}
}

// Called to bind functionality to input
void ANpcBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}



void ANpcBase::NameWidgetCallback()
{
	m_NpcInfoBarWidget->SetName(m_NpcInfo.Name);
}



void ANpcBase::TriggerBeginOverlap(UPrimitiveComponent* OverlapCom, AActor* OtherActor,
	UPrimitiveComponent* OtherCom,int32 OtherBodyIndex,bool bFromSweep,
	const FHitResult& SweepResult)
{
	PrintViewport(1.f,FColor::Red,TEXT("Begin Trigger"));
	m_TriggerBeginDelegate.Broadcast();
	
	ARPGGameModeBase* GameMode = Cast<ARPGGameModeBase>(GetWorld()->GetAuthGameMode());
	if(IsValid(GameMode))
	{
		UMainHUD* MainHud = GameMode->GetMainHUD();

		if(IsValid(MainHud))
		{
			MainHud->ShowNpcTalkKey(true);
		}
	}
	
	Player = Cast<ARPG_PlayerCharacter>(OtherActor);

	if(Player)
	{
		Player->SetInteractNpc(this);
	}
}

void ANpcBase::TriggerEndOverlap(UPrimitiveComponent* OverlapCom, AActor* OtherActor,
	UPrimitiveComponent* OtherCom,int32 OtherBodyIndex)
{
	PrintViewport(1.f,FColor::Red,TEXT("End Trigger"));
	m_TriggerEndDelegate.Broadcast();
	ARPGGameModeBase* GameMode = Cast<ARPGGameModeBase>(GetWorld()->GetAuthGameMode());
	if(IsValid(GameMode))
	{
		UMainHUD* MainHud = GameMode->GetMainHUD();

		if(IsValid(MainHud))
		{
			MainHud->ShowNpcTalkKey(false);
			MainHud->ShowNpcDialogue(false);
		}
	}
	if(Player)
	{
		Player->ShowMouseCursor(false);
		Player->SetInteractNpc(nullptr);
		Player=nullptr;
	}
}

void ANpcBase::SetDialogue()
{
	
	ARPGGameModeBase* GameMode = Cast<ARPGGameModeBase>(GetWorld()->GetAuthGameMode());
	if(IsValid(GameMode))
	{
		UMainHUD* MainHud = GameMode->GetMainHUD();

		if(IsValid(MainHud))
		{
			MainHud->ShowNpcDialogue(true);
			UNpcDialogue* NpcDialogue = MainHud->GetNpcDialogue();

			if(IsValid(NpcDialogue))
			{
				NpcDialogue->SetNpc(this);
				NpcDialogue->SetName(m_NpcInfo.Name);
				if(m_NpcInfo.Type==1)
				{
					if(MainHud->GetQuestWidget()->QuestClearCheck(m_QuestProgress)==false)
					{
						if(m_ordered)
						{
							NpcDialogue->SetNpcDialogue(m_NpcInfo.Dialogue2[0]);
						}
						else
							NpcDialogue->SetNpcDialogue(m_NpcInfo.Dialogue[m_QuestProgress]);
					}
					else if(m_ordered)
					{
						NpcDialogue->SetNpcDialogue(m_NpcInfo.Dialogue2[1]);
					}
				}
				else if(m_NpcInfo.Type==2)
				{
					if(m_DialogueProgress<m_NpcInfo.Dialogue.Num())
						NpcDialogue->SetNpcDialogue(m_NpcInfo.Dialogue[m_DialogueProgress]);
					else
					{
						m_DialogueProgress = 0;
						NpcDialogue->SetNpcDialogue(m_NpcInfo.Dialogue[m_DialogueProgress]);
					}
				}
			}
		}
	}
}

