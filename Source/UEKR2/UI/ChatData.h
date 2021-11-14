// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "UObject/NoExportTypes.h"
#include "ChatData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class UEKR2_API UChatData : public UObject
{
	GENERATED_BODY()

public:	
	UChatData();
private:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	FString m_Msg;

public:
	void SetMessage(const FString& Msg)
	{
		m_Msg = Msg;
	}
};
