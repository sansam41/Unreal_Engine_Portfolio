// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"

class UEKR2_API RecvQueue
{
	public:
	RecvQueue();
	~RecvQueue();

	private:
	FCriticalSection	m_Crt;
	RecvQueueData		m_Queue[200];
	int32				m_Head;
	int32				m_Tail;
	int32				m_Size;

	public:
	void Push(int32 Protocol, int32 Length, uint8* Packet);
	bool Pop(int32& Protocol, int32& Length, uint8* Packet);
	bool Empty();
	int32 Size();
};
