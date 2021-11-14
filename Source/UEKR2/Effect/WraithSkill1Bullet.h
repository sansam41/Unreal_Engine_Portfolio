// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "OrbitBullet.h"
#include "../GameInfo.h"
#include "ParticleProjectile.h"
#include "WraithSkill1Bullet.generated.h"

/**
 * 
 */
UCLASS()
class UEKR2_API AWraithSkill1Bullet : public AParticleProjectile
{
	GENERATED_BODY()
	public:	
	// Sets default values for this actor's properties
	AWraithSkill1Bullet();

	private:
	int32 m_Attack;
	class APlayerCharacter* m_Owner;
	AOrbitBullet* Bullet1;
	AOrbitBullet* Bullet2;
	AOrbitBullet* Bullet3;
	public:
	void SetAttack(int32 Attack)
	{
		m_Attack = Attack;
	}
	void SetOwner(class APlayerCharacter* Player)
	{
		m_Owner = Player;
		Bullet1->SetOwner(Player);
		Bullet2->SetOwner(Player);
		Bullet3->SetOwner(Player);
		
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
