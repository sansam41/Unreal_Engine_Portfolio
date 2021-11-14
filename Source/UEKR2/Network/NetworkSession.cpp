// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkSession.h"
#include "PacketStream.h"

NetworkSession::NetworkSession()
{
}

NetworkSession::~NetworkSession()
{
	Close();
}


bool NetworkSession::Connect(const FString& IPAddr, int32 Port)
{
	// 소켓을 생성한다.
	m_Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(
		NAME_Stream,	//연결 지향형
		TEXT("default"),
		false);

	FIPv4Address	ip;
	FIPv4Address::Parse(IPAddr, ip);	//IP주소 생성

	TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();

	addr->SetIp(ip.Value);
	addr->SetPort(Port);

	m_Connect = m_Socket->Connect(*addr);

	
	return true;
}
void NetworkSession::Close()
{
	if(m_Socket)
	{
		m_Socket->Close();
		m_Socket = nullptr;
	}
}


bool NetworkSession::Read(int32& Protocol, int32& Length, uint8* Packet)
{
	bool Result = m_Socket->Recv(m_RecvPacket,PACKET_SIZE,Length,ESocketReceiveFlags::None);

	if(!Result || Length <= 0)
		return false;

	// 읽어온 패킷으로부터 프로토콜과 실제 패킷부분의 길이, 패킷 내용을 분리한다.
	PacketStream stream;
	stream.SetBuffer(m_RecvPacket);

	stream.Read(&Protocol, sizeof(int32));
	stream.Read(&Length, sizeof(int32));
	stream.Read(Packet, Length);

	return  true;
}
bool NetworkSession::Write(int32 Protocol, int32 Length, uint8* Packet)
{
	// 보내고자 하는 프로토콜, 길이, 패킷 내용을 하나의 버퍼에 넣어서 보내주도록 한다.
	PacketStream stream;
	stream.SetBuffer(m_SendPacket);

	stream.Write(&Protocol, sizeof(int32));
	stream.Write(&Length, sizeof(int32));
	stream.Write(Packet, Length);
	
	return  m_Socket->Send(m_SendPacket,Length + 8, Length);
	
}