// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "DestructibleProjectile.generated.h"

UCLASS()
class UEKR2_API ADestructibleProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADestructibleProjectile();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* m_Body;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UDestructibleComponent* m_Mesh;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* m_Movement;

	bool	m_DestroyEnable;
	float	m_DestroyTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	m_DestroyTimeMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float m_Distance;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
		void ProjectileStop(const FHitResult& result);

protected:
	virtual void StopEvent(const FHitResult& result);
};
