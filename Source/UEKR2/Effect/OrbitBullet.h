// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "UEKR2/Player/PlayerCharacter.h"
#include "OrbitBullet.generated.h"

UCLASS()
class UEKR2_API AOrbitBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOrbitBullet();

public:
	class UOribitBulletMovement* m_Movement;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* m_Body;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* m_Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* m_Particle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* m_ParticleMovement;
	float m_Degree;

private:
	int32 m_Attack;
	class APlayerCharacter* m_Owner;

public:
	void SetAttack(int32 Attack)
	{
		m_Attack = Attack;
	}
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void SetAttach(AActor* Parent);
	void SetRadian(float Radian);
	
	void SetOwner(class APlayerCharacter* Player)
	{
		m_Owner = Player;
			
	}

	
public:
	UFUNCTION()
	void ProjectileStop(const FHitResult& result);


protected:
	void StopEvent(const FHitResult& result);
};
