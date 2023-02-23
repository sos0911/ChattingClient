// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "UW_WaitRoom.generated.h"

class UScrollBox;
class UEditableTextBox;
class UButton;

class UCCNetworkManager;
/**
 * 
 */
UCLASS()
class CHATTINGCLIENT_API UUW_WaitRoom : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Meta = (BindWidget))
		UScrollBox* ScrollBox_InfoList;
	UPROPERTY(Meta = (BindWidget))
		UScrollBox* ScrollBox_ChatList;

	UPROPERTY(Meta = (BindWidget))
		UButton* Button_RoomList_Renew;
	UPROPERTY(Meta = (BindWidget))
		UButton* Button_Room_Join;
	UPROPERTY(Meta = (BindWidget))
		UButton* Button_Room_Make;
	UPROPERTY(Meta = (BindWidget))
		UButton* Button_Room_Info;
	UPROPERTY(Meta = (BindWidget))
		UButton* Button_Player_Info;
	UPROPERTY(Meta = (BindWidget))
		UButton* Button_PlayerList_Renew;
	UPROPERTY(Meta = (BindWidget))
		UButton* Button_Exit;

	UPROPERTY(Meta = (BindWidget))
		UEditableTextBox* Input_PlayerName;
	UPROPERTY(Meta = (BindWidget))
		UEditableTextBox* Input_WhisperMsg;

	UFUNCTION(BlueprintCallable)
		void RoomListRenewButtonCallback();
	UFUNCTION(BlueprintCallable)
		void RoomJoinButtonCallback();
	UFUNCTION(BlueprintCallable)
		void RoomMakeButtonCallback();
	UFUNCTION(BlueprintCallable)
		void RoomInfoButtonCallback();
	UFUNCTION(BlueprintCallable)
		void PlayerInfoButtonCallback();
	UFUNCTION(BlueprintCallable)
		void PlayerListRenewButtonCallback();
	UFUNCTION(BlueprintCallable)
		void ProgramExitCallback();

	UFUNCTION(BlueprintCallable)
		void SendWhisperCallback(const FText& Text, ETextCommit::Type CommitMethod);

	UFUNCTION(BlueprintCallable)
		class ACCPlayerController* GetPlayerController();

	UCCNetworkManager* NetworkManager;

protected:
	virtual void NativeConstruct() override;

public:
	// donghyun : 채팅방 / 플레이어 목록 UI 갱신 함수
	void SetInfoListUI(const FString& msg);
	// donghyun : 귓속말 UI 갱신 함수
	void SetWhisperUI(const FString& msg);
};
