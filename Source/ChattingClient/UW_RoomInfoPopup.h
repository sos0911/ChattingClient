// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "UW_RoomInfoPopup.generated.h"

class UScrollBox;
class UEditableTextBox;
class UButton;

class UCCNetworkManager;

/**
 *
 */
UCLASS()
class CHATTINGCLIENT_API UUW_RoomInfoPopup : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(Meta = (BindWidget))
		UScrollBox* ScrollBox_RoomInfo;

	UPROPERTY(Meta = (BindWidget))
		UEditableTextBox* Input_RoomNum;
	UPROPERTY(Meta = (BindWidget))
		UButton* Button_Confirm;
	UPROPERTY(Meta = (BindWidget))
		UButton* Button_Exit;


	UFUNCTION(BlueprintCallable)
		void RoomInfoRenewButtonCallback();
	UFUNCTION(BlueprintCallable)
		void RoomInfoExitCallback();

	UFUNCTION(BlueprintCallable)
		class ACCPlayerController* GetPlayerController();

	UCCNetworkManager* NetworkManager;

protected:
	virtual void NativeConstruct() override;

public:
	// donghyun : 채팅방 정보 갱신 함수
	void SetRoomInfoUI(const FString& msg);
};


