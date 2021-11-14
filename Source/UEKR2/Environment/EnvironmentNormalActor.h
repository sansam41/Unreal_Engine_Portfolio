// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "EnvironmentNormalActor.generated.h"

UCLASS()
class UEKR2_API AEnvironmentNormalActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnvironmentNormalActor();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* m_Mesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* m_Body;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool m_DepthSilhouette;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool m_CameraCollision;

	UMaterialInstanceDynamic* m_DynamicMaterial;

public:
	bool GetDepthSilhouette() const
	{
		return m_DepthSilhouette;
	}
	
	void SetCameraCollision(bool Collision)
	{
		m_CameraCollision = Collision;

		if(Collision)
		{
			m_DynamicMaterial->SetScalarParameterValue(TEXT("SilhouetteEnable"),1.f);
		}
		else
		{
			m_DynamicMaterial->SetScalarParameterValue(TEXT("SilhouetteEnable"),0.f);
		}
	}

	bool GetCameraCollision() const
	{
		return m_CameraCollision;
	}
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
