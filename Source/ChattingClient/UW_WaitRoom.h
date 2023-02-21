// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/ScrollBox.h"

#include "UW_WaitRoom.generated.h"

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
		UScrollBox* ScrollBox_PlayerList;
	UPROPERTY(Meta = (BindWidget))
		UScrollBox* ScrollBox_RoomList;

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
		UButton* Button_Send_Whisper;
	UPROPERTY(Meta = (BindWidget))
		UButton* Button_PlayerList_Renew;

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
		void SendWhisperButtonCallback();
	UFUNCTION(BlueprintCallable)
		void PlayerListRenewButtonCallback();

	UFUNCTION(BlueprintCallable)
		class APlayerController* GetPlayerController();

	UCCNetworkManager* NetworkManager;

protected:
	virtual void NativeConstruct();
};
