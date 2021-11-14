// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "../AssetManager/AssetPathMain.h"
#include "../UI/MainHUD.h"
#include "GameFramework/GameModeBase.h"
#include "RPGGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API ARPGGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	public:
	ARPGGameModeBase();

	protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UMainHUD> m_MainHUDClass;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	TArray<TSubclassOf<APawn>> m_PlayerClassArray;

	UMainHUD* m_MainHUD;

	UAssetPathMain* m_MainAssetPath;

	public:

	UMainHUD* GetMainHUD()
	{
		return m_MainHUD;
	}

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
};