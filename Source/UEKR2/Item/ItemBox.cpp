// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBox.h"

#include "UEKR2/UEKR2GameInstance.h"
#include "../UEKR2GameModeBase.h"
#include "../UI/InventoryList.h"
#include "../UI/InventoryTile.h"
#include "../UI/MainHUD.h"
#include "../UI/QuestWidget.h"

// Sets default values
AItemBox::AItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	m_Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	SetRootComponent(m_Box);

	m_Mesh->SetupAttachment(m_Box);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>	MeshAsset(TEXT("StaticMesh'/Game/Item/ItemBox.ItemBox'"));

	if (MeshAsset.Succeeded())
		m_Mesh->SetStaticMesh(MeshAsset.Object);

	m_Box->SetBoxExtent(FVector(50.f, 50.f, 50.f));
	m_Mesh->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));

	m_Box->SetCollisionProfileName(TEXT("PlayerTrigger"));
	m_Box->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void AItemBox::BeginPlay()
{
	Super::BeginPlay();

	m_Box->OnComponentBeginOverlap.AddDynamic(this,&AItemBox::ItemBeginOverlap);
}

// Called every frame
void AItemBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void AItemBox::ItemBeginOverlap(UPrimitiveComponent* OverlapCom, AActor* OtherActor,
	UPrimitiveComponent* OtherCom,int32 OtherBodyIndex,bool bFromSweep,
	const FHitResult& SweepResult)
{
	UUEKR2GameInstance* GameInst = Cast<UUEKR2GameInstance>(GetWorld()->GetGameInstance());

	if(GameInst)
	{
		const FUIItemTableInfo* ItemInfo = GameInst->FindUIItemInfo(m_ItemName);
		if(ItemInfo)
		{
			// 인벤토리에 아이템을 추가한다.
			AUEKR2GameModeBase* GameMode =Cast<AUEKR2GameModeBase>(GetWorld()->GetAuthGameMode());

			if(GameMode)
			{
				GameMode->GetMainHUD()->GetMainInventoryList()->AddItem(ItemInfo);
				GameMode->GetMainHUD()->GetInventoryTile()->AddItem(ItemInfo);
				GameMode->GetMainHUD()->GetQuestWidget()->QuestCheck(EQuestType::Collection,
					m_ItemName);
			}
		}
	}
	Destroy();
}