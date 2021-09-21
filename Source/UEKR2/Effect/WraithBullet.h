// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "ParticleProjectile.h"
#include "WraithBullet.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API AWraithBullet : public AParticleProjectile
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	AWraithBullet();

private:
	int32 m_Attack;
	class APlayerCharacter* m_Owner;

public:
	void SetAttack(int32 Attack)
	{
		m_Attack = Attack;
	}
	void SetOwner(class APlayerCharacter* Player)
	{
		m_Owner = Player;
	}
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void StopEvent(const FHitResult& result);
};

