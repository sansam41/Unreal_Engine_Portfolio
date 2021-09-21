// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "UI/CharacterSelectHUD.h"
#include "GameFramework/GameModeBase.h"
#include "CharacterSelectGameMode.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API ACharacterSelectGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ACharacterSelectGameMode();

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UCharacterSelectHUD> m_SelectHUDClass;

	UCharacterSelectHUD* m_SelectHUD;

public:

	UCharacterSelectHUD* GetSelectHUD()
	{
		return m_SelectHUD;
	}

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void BeginPlay() override;
	
};
