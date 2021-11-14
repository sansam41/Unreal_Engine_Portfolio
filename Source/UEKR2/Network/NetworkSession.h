// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"

class UEKR2_API NetworkSession
{
	public:
	NetworkSession();
	~NetworkSession();

	private:
	FSocket* m_Socket;
	bool	m_Connect;
	uint8	m_RecvPacket[PACKET_SIZE];
	uint8	m_SendPacket[PACKET_SIZE];

	public:
	bool Connect(const FString& IPAddr, int32 Port);
	void Close();
	bool Read(int32& Protocol, int32& Length, uint8* Packet);
	bool Write(int32 Protocol, int32 Length, uint8* Packet);
};
