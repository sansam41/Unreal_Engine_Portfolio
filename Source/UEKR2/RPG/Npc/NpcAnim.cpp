// Fill out your copyright notice in the Description page of Project Settings.


#include "NpcAnim.h"

UNpcAnim::UNpcAnim() {
	
	m_AnimType = ENpcAnimType::Idle;
}

void UNpcAnim::NativeInitializeAnimation() {
	Super::NativeInitializeAnimation();
}


void UNpcAnim::NativeUpdateAnimation(float DeltaSeconds) {
	Super::NativeUpdateAnimation(DeltaSeconds);

}