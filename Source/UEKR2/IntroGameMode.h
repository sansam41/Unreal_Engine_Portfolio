// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "GameFramework/GameModeBase.h"
#include "UI/IntroWidget.h"
#include "IntroGameMode.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API AIntroGameMode : public AGameModeBase
{
	GENERATED_BODY()
	public:
	AIntroGameMode();

	protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UIntroWidget> m_IntroClass;

	UIntroWidget* m_IntroWidget;

	public:

	UIntroWidget* GetIntroWidget()
	{
		return m_IntroWidget;
	}

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void BeginPlay() override;
	
};
