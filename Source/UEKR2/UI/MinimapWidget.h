// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/Image.h"
#include "Blueprint/UserWidget.h"
#include "MinimapWidget.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API UMinimapWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UImage* m_PlayerArrow;

	TArray<UImage*>		m_MonsterArray;
	int32				m_AddCount;

protected:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

private:
	void CreateMonsterArray();

public:
	void RotationArrow(float Yaw);
	void AddMonster(const FVector& Pos);
	void ClearMonster();
};
