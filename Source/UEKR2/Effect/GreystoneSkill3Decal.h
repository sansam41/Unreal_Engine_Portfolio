// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "EffectDecal.h"
#include "GreystoneSkill3Decal.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API AGreystoneSkill3Decal : public AEffectDecal
{
	GENERATED_BODY()
	public:
	AGreystoneSkill3Decal();
	protected:
	UMaterialInstanceDynamic* m_Material;
	float m_Glow;
	float m_Dir;
	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
