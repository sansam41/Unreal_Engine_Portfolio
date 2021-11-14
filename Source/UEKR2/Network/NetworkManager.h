// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "RecvQueue.h"

class UEKR2_API NetworkManager
{
	private:
	NetworkManager();
	~NetworkManager();

	private:
	class NetworkSession* m_Session;
	bool		m_Run;
	class RecvThread* m_Thread;
	FRunnableThread* m_RunnableThread;
	RecvQueue		m_RecvQueue;

	public:
	class NetworkSession* GetSession()
	{
		return m_Session;
	}

	RecvQueue* GetQueue()
	{
		return &m_RecvQueue;
	}

	public:
	bool Init();

	private:
	static NetworkManager* m_Inst;

	public:
	static NetworkManager* GetInst()
	{
		if (!m_Inst)
			m_Inst = new NetworkManager;

		return m_Inst;
	}

	static void DestroyInst()
	{
		if (m_Inst)
		{
			delete	m_Inst;
			m_Inst = nullptr;
		}
	}
};
