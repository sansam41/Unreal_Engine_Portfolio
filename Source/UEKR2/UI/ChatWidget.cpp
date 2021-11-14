// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatWidget.h"
#include "../Network/NetworkManager.h"
#include "../Network/NetworkSession.h"
#include "ChatData.h"

void UChatWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_ChatList = Cast<UListView>(GetWidgetFromName(TEXT("ChatList")));
	m_Input = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("TextInput")));
	m_SendButton = Cast<UButton>(GetWidgetFromName(TEXT("SendButton")));

	m_SendButton->OnClicked.AddDynamic(this, &UChatWidget::SendButtonClick);
}

void UChatWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UChatWidget::SendButtonClick()
{
	FString	InputText = m_Input->GetText().ToString();

	PrintViewport(1.f, FColor::Red, InputText);
	AddMsg(InputText);
	// 서버로 내용을 전송한다.
	NetworkSession* Session = NetworkManager::GetInst()->GetSession();

	int32	Length = InputText.Len() * sizeof(TCHAR);

	uint8	Packet[PACKET_SIZE] = {};
	FMemory::Memcpy(Packet, *InputText, Length);

	Session->Write((int)NetworkProtocol::Chat, Length, Packet);
}

void UChatWidget::AddMsg(const FString& Msg)
{
	UChatData* Data = NewObject<UChatData>(this, UChatData::StaticClass());

	Data->SetMessage(Msg);

	m_ChatList->AddItem(Data);

	m_ChatList->ScrollToBottom();
}
