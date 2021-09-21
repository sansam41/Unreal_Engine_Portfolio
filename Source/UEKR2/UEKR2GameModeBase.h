// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameInfo.h"
#include "GameFramework/GameModeBase.h"
#include "UI/MainHUD.h"
#include "UEKR2GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API AUEKR2GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AUEKR2GameModeBase();

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UMainHUD> m_MainHUDClass;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	TArray<TSubclassOf<APawn>> m_PlayerClassArray;

	UMainHUD* m_MainHUD;

public:

	UMainHUD* GetMainHUD()
	{
		return m_MainHUD;
	}

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
};
