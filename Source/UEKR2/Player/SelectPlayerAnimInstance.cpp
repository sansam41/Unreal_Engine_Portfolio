// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectPlayerAnimInstance.h"


USelectPlayerAnimInstance::USelectPlayerAnimInstance() {

	m_AnimType = ESelectPlayerAnimType::Idle;


}

//void USelectPlayerAnimInstance::NativeInitializeAnimation() {
//	Super::NativeInitializeAnimation();
//}
//void USelectPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds) {
//	Super::NativeUpdateAnimation(DeltaSeconds);
//}

UFUNCTION()
void USelectPlayerAnimInstance::AnimNotify_TransitionIdle()
{
	m_AnimType = ESelectPlayerAnimType::Idle;
}