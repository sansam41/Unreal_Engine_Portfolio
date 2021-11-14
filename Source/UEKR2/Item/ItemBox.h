// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "ItemBox.generated.h"

UCLASS()
class UEKR2_API AItemBox : public AActor
{
	GENERATED_BODY()
	
	public:	
	// Sets default values for this actor's properties
	AItemBox();

	protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* m_Box;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* m_Mesh;

	FString m_ItemName;
public:
	void SetItemName(const FString& Name)
	{
		m_ItemName = Name;
	}

	void SetMesh(UStaticMesh* Mesh)
	{
		m_Mesh->SetStaticMesh(Mesh);
	}
	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
	void ItemBeginOverlap(UPrimitiveComponent* OverlapCom, AActor* OtherActor,
		UPrimitiveComponent* OtherCom,int32 OtherBodyIndex,bool bFromSweep,
		const FHitResult& SweepResult);

};