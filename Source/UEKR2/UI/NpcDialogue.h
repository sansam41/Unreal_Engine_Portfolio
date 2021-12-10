// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/MultiLineEditableTextBox.h"
#include "Components/TextBlock.h"
#include "NpcDialogue.generated.h"

/**
 * 
 */


DECLARE_DELEGATE(FNpcDialogueDelegate);


UCLASS()
class UEKR2_API UNpcDialogue : public UUserWidget
{
	GENERATED_BODY()
		
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	UTextBlock*  m_NameText;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	UMultiLineEditableTextBox*  m_NpcDialogue;
	
	FNpcDialogueDelegate m_NpcDialogueDelegate;


	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	UButton*  m_YesButton;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	UButton*  m_NoButton;

	class ANpcBase* m_Npc;


	
public:
	void SetName(const FString& Name)
	{
		m_NameText->SetText(FText::FromString(Name));
	}
	void SetNpcDialogue(const FString& Text)
	{
		m_NpcDialogue->SetText(FText::FromString(Text));
	}
	void SetNpc(ANpcBase* Npc)
	{
		m_Npc = Npc;
	}
	

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
public:
	template <typename T>
	void SetDelegate(T* Obj, void(T::* Func)())
	{
		m_NpcDialogueDelegate.BindUObject(Obj, Func);
	}
public:
	UFUNCTION()
	void YesButtonClicked();
	
	UFUNCTION()
	void NoButtonClicked();
};
