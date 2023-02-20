// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/EditableTextBox.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "CCNetworkManager.h"

#include "UW_Login.generated.h"

/**
 * 
 */
UCLASS()
class CHATTINGCLIENT_API UUW_Login : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(Meta = (BindWidget))
		UEditableTextBox* Input_IP;
	UPROPERTY(Meta = (BindWidget))
		UEditableTextBox* Input_Port;
	UPROPERTY(Meta = (BindWidget))
		UButton* Button_Submit;
	UFUNCTION(BlueprintCallable)
		void SummitButtonCallback();
	
	UCCNetworkManager* NetworkManager;

protected:
	virtual void NativeConstruct();
};
