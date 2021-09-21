// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "DestructibleProjectile.h"
#include "GreystoneSkill2.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API AGreystoneSkill2 : public ADestructibleProjectile
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGreystoneSkill2();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	UParticleSystemComponent* m_Particle;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	float m_Damage;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void StopEvent(const FHitResult& result);
};
