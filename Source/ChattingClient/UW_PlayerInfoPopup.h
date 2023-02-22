// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/ScrollBox.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "Runtime/UMG/Public/Components/EditableTextBox.h"

#include "UW_PlayerInfoPopup.generated.h"

class UCCNetworkManager;

/**
 * 
 */
UCLASS()
class CHATTINGCLIENT_API UUW_PlayerInfoPopup : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(Meta = (BindWidget))
		UScrollBox* ScrollBox_PlayerInfo;

	UPROPERTY(Meta = (BindWidget))
		UEditableTextBox* Input_PlayerName;
	UPROPERTY(Meta = (BindWidget))
		UButton* Button_Confirm;
	UPROPERTY(Meta = (BindWidget))
		UButton* Button_Exit;


	UFUNCTION(BlueprintCallable)
		void PlayerInfoRenewButtonCallback();
	UFUNCTION(BlueprintCallable)
		void PlayerInfoExitCallback();

	UFUNCTION(BlueprintCallable)
		class ACCPlayerController* GetPlayerController();

	UCCNetworkManager* NetworkManager;

protected:
	virtual void NativeConstruct();

public:
	void SetPlayerInfoUI(const FString& msg);
};
