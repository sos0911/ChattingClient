// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "UW_ChattingRoom.generated.h"

class UScrollBox;
class UEditableTextBox;
class UButton;

class UCCNetworkManager;

/**
 *
 */
UCLASS()
class CHATTINGCLIENT_API UUW_ChattingRoom : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(Meta = (BindWidget))
		UScrollBox* ScrollBox_Chat;

	UPROPERTY(Meta = (BindWidget))
		UEditableTextBox* Input_Chat;

	UPROPERTY(Meta = (BindWidget))
		UButton* Button_Exit;


	UFUNCTION(BlueprintCallable)
		void RoomExitCallback();
	UFUNCTION(BlueprintCallable)
		void SendChattingCallback(const FText& Text, ETextCommit::Type CommitMethod);

	UFUNCTION(BlueprintCallable)
		class ACCPlayerController* GetPlayerController();

	UCCNetworkManager* NetworkManager;

protected:
	virtual void NativeConstruct() override;

public:
	// donghyun : 채팅방 로그 갱신 함수
	void RenewChattingRoomLog(const FString& msg);
};


