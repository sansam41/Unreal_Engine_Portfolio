// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "UI/StartWidget.h"
#include "GameFramework/GameModeBase.h"
#include "StartGameMode.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API AStartGameMode : public AGameModeBase
{
	GENERATED_BODY()
	public:
	AStartGameMode();

	protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UStartWidget> m_StartWidgetClass;

	UStartWidget* m_StartWidgetHUD;

	public:

	UStartWidget* GetMainHUD()
	{
		return m_StartWidgetHUD;
	}

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void BeginPlay() override;
};
