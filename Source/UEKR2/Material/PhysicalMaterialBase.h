// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "PhysicalMaterialBase.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API UPhysicalMaterialBase : public UPhysicalMaterial
{
	GENERATED_BODY()
	UPhysicalMaterialBase();

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	USoundBase* m_Sound;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	UParticleSystem* m_Particle;

public:
	 void SetSound(const FString& Path);
	 void SetParticle(const FString& Path);

public:
	USoundBase* GetSound()
	{
		return m_Sound;
	}
	UParticleSystem* GetParticle()
	{
		return m_Particle;
	}
};
