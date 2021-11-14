// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"

/**
* 
*/
class UEKR2_API PacketStream
{
	public:
	PacketStream();
	~PacketStream();

	private:
	uint8* m_Buffer;
	int32	m_Length;

	public:
	void SetBuffer(uint8* Buffer)
	{
		m_Buffer = Buffer;
	}

	int32 GetLength()
	{
		return m_Length;
	}

	public:
	void Read(void* Data, int32 Size);
	void Write(void* Data, int32 Size);
};
