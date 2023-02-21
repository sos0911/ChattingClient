// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/EditableTextBox.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "CCNetworkManager.h"
#include "CCPlayerController.h"
#include "CCPlayerState.h"
#include "Kismet/GameplayStatics.h"

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
		UEditableTextBox* Input_Nickname;
	UPROPERTY(Meta = (BindWidget))
		UEditableTextBox* Input_IP;
	UPROPERTY(Meta = (BindWidget))
		UEditableTextBox* Input_Port;
	UPROPERTY(Meta = (BindWidget))
		UButton* Button_Submit;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* Text_Nickname;
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* Text_IP;
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* Text_Port;

	UFUNCTION(BlueprintCallable)
		void SummitButtonCallback();
	UFUNCTION(BlueprintCallable)
		class APlayerController* GetPlayerController();
	
	UCCNetworkManager* NetworkManager;

protected:
	virtual void NativeConstruct();
};
