// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "PlayerCharacter.h"
#include "../Environment/EnvironmentNormalActor.h"
#include "../Monster/Monster.h"

AMainPlayerController::AMainPlayerController()
{
	bShowMouseCursor=true;
	m_ShowUI=false;
}
void AMainPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
/*
	for (auto& CollisionActor : m_CollisionEnvironmentActor)
	{
		CollisionActor->SetCameraCollision(false);
	}

	APlayerCharacter* PlayerActor = Cast<APlayerCharacter>(GetPawn());

	FVector	CameraLoc = PlayerActor->GetCameraLocation();
	FVector	PlayerLoc = GetPawn()->GetActorLocation();

	FCollisionQueryParams	params(NAME_None, false, this);

	TArray<FHitResult>	HitResultArray;
	bool Hit = GetWorld()->LineTraceMultiByChannel(HitResultArray, CameraLoc,
		PlayerLoc, ECollisionChannel::ECC_Camera,
		params);

	if (Hit)
	{
		for (auto& result : HitResultArray)
		{
			AEnvironmentNormalActor* EnvironmentActor =
				Cast<AEnvironmentNormalActor>(result.GetActor());

			if (EnvironmentActor)
			{
				if (EnvironmentActor->GetDepthSilhouette())
				{
					EnvironmentActor->SetCameraCollision(true);
				}

				bool	Overlap = false;

				for (auto& CollisionActor : m_CollisionEnvironmentActor)
				{
					if (CollisionActor == EnvironmentActor)
					{
						Overlap = true;
						break;
					}
				}

				if (!Overlap)
				{
					m_CollisionEnvironmentActor.Add(EnvironmentActor);
				}
			}
		}
	}
	FHitResult	result;

	Hit = GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel9,
		false, result);

	if (Hit)
	{
		AMonster* Monster =
			Cast<AMonster>(result.GetActor());

		if (Monster)
		{
			CurrentMouseCursor = EMouseCursor::TextEditBeam;
			//rintViewport(1.f, FColor::Red, TEXT("Monster Mouse On"));
		}

		else
		{
			CurrentMouseCursor = EMouseCursor::Default;
		}

		AEnvironmentNormalActor* EnvironmentActor =
						Cast<AEnvironmentNormalActor>(result.GetActor());
		
		
	}

	
	/*for (auto& CollisionActor : m_CollisionEnvironmentActor)
	{
	if (!CollisionActor->GetCameraCollision())
	{
	m_CollisionEnvironmentActor.Remove(CollisionActor);
	PrintViewport(1.f, FColor::Red, TEXT("Remove"));
	}
	}*/
/*
	for (int32 i = 0; i < m_CollisionEnvironmentActor.Num();)
	{
		if (!m_CollisionEnvironmentActor[i]->GetCameraCollision())
		{
			//m_CollisionEnvironmentActor.Remove(m_CollisionEnvironmentActor[i]);
			m_CollisionEnvironmentActor.RemoveAt(i);
		}

		else
			++i;
	}
*/	
}