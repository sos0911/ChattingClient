// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"


#include "UW_PlayerInfoPopup.generated.h"

class UScrollBox;
class UEditableTextBox;
class UButton;

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
	virtual void NativeConstruct() override;

public:
	// donghyun : 플레이어 정보 갱신 함수
	void SetPlayerInfoUI(const FString& msg);
};
