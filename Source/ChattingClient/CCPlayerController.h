// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
//#include "UW_Login.h"
#include "CCPlayerState.h"

#include "CCPlayerController.generated.h"


class UUW_Login;
class UUW_WaitRoom;
class UUW_PlayerInfoPopup;
class UUW_RoomInfoPopup;
class UUW_ChattingRoom;
class UUW_JoinRoomPopup;
class UUW_MakeRoomPopup;

class UCCNetworkManager;
/**
 * 
 */
UCLASS()
class CHATTINGCLIENT_API ACCPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACCPlayerController();
	virtual void BeginPlay() override;
	/*virtual void SetupInputComponent() override;*/
	virtual void PlayerTick(float Deltatime) override;
	void SetPlayerState(const EPlayerState& StateFlag);
	void UndoPlayerState();
	EPlayerState& GetPlayerState();

	// donghyun : 여기서부터는 서버로부터 받아온 쿼리에 대한 처리
	void SetConntectedUI();
	void SetLoginUI();
	void SetInfoListUI(const FString& msg);
	void SetPlayerInfoUI(const FString& msg);
	void MakePlayerInfoPopup();
	void MakeRoomInfoPopup();
	void SetRoomInfoUI(const FString& msg);
	void MakeRoomPopup();
	void RenewChattingRoomLog(const FString& msg);
	void WaitRoomToChattingRoom();
	void JoinRoomPopup();
	void ChattingRoomToWaitRoom();
	void SetJoinRoomResultUI(const FString& msg);
	void RemoveJoinRoomPopup();
	void SetWhisperUI(const FString& msg);
	void SetLoginNotifyUI(const FString& msg);

	UUserWidget* FindAndMakeClassObjects(FString& Path);

	FString WB_Login_Path = TEXT("/Game/UI/BP_Login");
	FString WB_WaitRoom_Path = TEXT("/Game/UI/BP_WaitRoom");
	FString WB_PlayerInfo_Path = TEXT("/Game/UI/BP_PlayerInfo_Popup");
	FString WB_RoomInfo_Path = TEXT("/Game/UI/BP_RoomInfo_Popup");
	FString WB_JoinRoom_Path = TEXT("/Game/UI/BP_JoinRoom_Popup");
	FString WB_MakeRoom_Path = TEXT("/Game/UI/BP_MakeRoom_Popup");
	FString WB_ChattingRoom_Path = TEXT("/Game/UI/BP_ChattingRoom");


private:
	/*TSubclassOf<UUW_Login> LoginUIClass;
	TSubclassOf<UUW_WaitRoom> WaitRoomUIClass;
	TSubclassOf<UUW_PlayerInfoPopup> PlayerInfoUIClass;

	UUW_Login* LoginUIObject;
	UUW_WaitRoom* WaitRoomUIObject;
	UUW_PlayerInfoPopup* PlayerInfoUIObject;*/

	UUW_Login* LoginUIObject;
	UUW_WaitRoom* WaitRoomUIObject;
	UUW_PlayerInfoPopup* PlayerInfoUIObject;
	UUW_RoomInfoPopup* RoomInfoUIObject;
	UUW_ChattingRoom* ChattingRoomUIObject;
	UUW_JoinRoomPopup* JoinRoomUIObject;
	UUW_MakeRoomPopup* MakeRoomUIObject;

	UCCNetworkManager* NetworkManagerPtr;
	ACCPlayerState* CCPlayerStatePtr;
};
