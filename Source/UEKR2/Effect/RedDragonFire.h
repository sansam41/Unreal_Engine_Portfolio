// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "ParticleProjectile.h"
#include "../Monster/Monster.h"
#include "RedDragonFire.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API ARedDragonFire : public AParticleProjectile
{
	GENERATED_BODY()
			
public:	
	// Sets default values for this actor's properties
	ARedDragonFire();

private:
	int32 m_Attack;
	class AMonster* m_Owner;

public:
	void SetAttack(int32 Attack)
	{
		m_Attack = Attack;
	}
	void SetOwner(class AMonster* Monster)
	{
		m_Owner = Monster;
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
