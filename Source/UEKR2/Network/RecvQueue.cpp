// Fill out your copyright notice in the Description page of Project Settings.


#include "RecvQueue.h"

RecvQueue::RecvQueue()	:
	m_Head(0),
	m_Tail(0),
	m_Size(0)
{
}

RecvQueue::~RecvQueue()
{
}

void RecvQueue::Push(int32 Protocol, int32 Length, uint8* Packet)
{
	FScopeLock lock(&m_Crt);
	int32 Tail =(m_Tail+1)%200;
	if(Tail == m_Head)
		return;

	m_Queue[Tail].Protocol = Protocol;
	m_Queue[Tail].Length = Length;

	FMemory::Memset(m_Queue[Tail].Packet,0,PACKET_SIZE);
	FMemory::Memcpy(m_Queue[Tail].Packet,Packet,Length);
	
	m_Tail = Tail;
	
	++m_Size;
}
bool RecvQueue::Pop(int32& Protocol, int32& Length, uint8* Packet)
{
	FScopeLock lock(&m_Crt);
	if(Empty())
		return false;

	int32 Head = (m_Head+1)%200;

	Protocol = m_Queue[Head].Protocol;
	Length = m_Queue[Head].Length;

	FMemory::Memcpy(Packet,m_Queue[Head].Packet,Length);

	m_Head = Head;

	
	--m_Size;
	
	return true;
}
bool RecvQueue::Empty()
{
	return m_Size==0;
}
int32 RecvQueue::Size()
{
	return m_Size;
}