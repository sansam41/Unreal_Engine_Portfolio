// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"

class UEKR2_API RecvThread	:
	public FRunnable
{
	public:
	RecvThread();
	~RecvThread();

	private:
	bool	m_Loop;
	class NetworkSession* m_Session;

	public:
	void SetSession(class NetworkSession* Session)
	{
		m_Session = Session;
	}

	public:
	virtual bool Init();
	virtual uint32 Run();
	virtual void Exit();
};
