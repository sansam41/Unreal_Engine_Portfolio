// Fill out your copyright notice in the Description page of Project Settings.


#include "MediaActor.h"

// Sets default values
AMediaActor::AMediaActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	m_MediaSound = CreateDefaultSubobject<UMediaSoundComponent>(TEXT("MediaSound"));

	SetRootComponent(m_Mesh);

	m_MediaSound->SetupAttachment(m_Mesh);
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh>	MeshAsset(TEXT("StaticMesh'/Game/Movie/Cube.Cube'"));
	//static ConstructorHelpers::FObjectFinder<UStaticMesh>	MeshAsset(TEXT("Material'/Game/Temp/IntroMediaTexture_Mat.IntroMediaTexture_Mat'"));

	if (MeshAsset.Succeeded())
		m_Mesh->SetStaticMesh(MeshAsset.Object);

	m_Mesh->SetRelativeRotation(FRotator(0.f, 90.f, 90.f));
	m_Mesh->SetRelativeScale3D(FVector(10.f, 10.f, 1.f));

	static ConstructorHelpers::FObjectFinder<UMediaPlayer>	MediaAsset(TEXT("MediaPlayer'/Game/Movie/IntroMedia.IntroMedia'"));

	if (MediaAsset.Succeeded())
		m_MediaAsset = MediaAsset.Object;

	m_MediaSound->SetMediaPlayer(m_MediaAsset);

	static ConstructorHelpers::FObjectFinder<UMediaTexture>	MediaTextureAsset(TEXT("MediaTexture'/Game/Movie/IntroMediaTexture.IntroMediaTexture'"));

	if (MediaTextureAsset.Succeeded())
		m_MediaTexture = MediaTextureAsset.Object;

	static ConstructorHelpers::FObjectFinder<UMediaSource>	MediaSourceAsset(TEXT("FileMediaSource'/Game/Movie/SampleVideo.SampleVideo'"));

	if (MediaSourceAsset.Succeeded())
		m_MediaSource = MediaSourceAsset.Object;
}

// Called when the game starts or when spawned
void AMediaActor::BeginPlay()
{
	Super::BeginPlay();

	m_MediaAsset->OpenSource(m_MediaSource);

	m_Material = m_Mesh->CreateDynamicMaterialInstance(0);

	m_Material->SetTextureParameterValue(TEXT("Texture"), m_MediaTexture);

	m_MediaSound->SetMediaPlayer(m_MediaAsset);
	
	m_MediaAsset->Play();

	
}

// Called every frame
void AMediaActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

