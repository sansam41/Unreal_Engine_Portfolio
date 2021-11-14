// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/PlayerController.h"
#include "SelectPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API ASelectPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ASelectPlayerController();

private:
	bool m_LButtonClick;
	EPlayerJob m_SelectJob;
	ACharacter* m_SelectCharacter;

public:
	EPlayerJob GetSelectJob() const
	{
		return m_SelectJob;
	}
public:
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
public:
	void MouseClick();
	void MouseRelese();
	void Picking();
	
};
