// Fill out your copyright notice in the Description page of Project Settings.


#include "RecvThread.h"
#include "NetworkSession.h"
#include "NetworkManager.h"
#include "RecvQueue.h"

RecvThread::RecvThread()	:
	m_Session(nullptr),
	m_Loop(true)
{
}

RecvThread::~RecvThread()
{
}


bool RecvThread::Init()
{
	return true;
}
uint32 RecvThread::Run()
{
	while(m_Loop)
	{
		uint8 Packet[PACKET_SIZE] = {};
		int32 Protocol = -1, Length = 0;
		
		bool Result = m_Session->Read(Protocol, Length, Packet);

		if(!Result)
			continue;

		RecvQueue* Queue = NetworkManager::GetInst()->GetQueue();

		Queue->Push(Protocol, Length, Packet);
	}
	
	return 0;
}

void RecvThread::Exit()
{
	m_Loop = false;
}