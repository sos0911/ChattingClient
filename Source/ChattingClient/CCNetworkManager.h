// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CCNetworkManager.generated.h" 

class ACCPlayerController;
class UGameInstance;
class FSocket;

/**
 * 
 */
UCLASS()
class CHATTINGCLIENT_API UCCNetworkManager : public UGameInstance
{
	GENERATED_BODY()

private:
	FSocket* socket;
	FString EncodedBuf;
	ACCPlayerController* PlayerController;

	virtual void Shutdown();

public:
	// donghyun : 소켓 연결
	UCCNetworkManager();
	void Initialize(const FString& ServerIP_Str, const FString& Port);
	// donghyun : 서버에 메세지 보내는 함수
	// 텔넷이 보낼때 '\r\n'을 무조건 뒤에 붙이므로
	// 이거 붙여서 보내야 통일 가능
	void sendMsg(const FString& msg);
	// donghyun : 서버에서 메세지 받는 함수
	void RecvMsg();
	// donghyun : 메세지 받은거 구분해서 흐름 넘겨주는 함수
	void JudgePacket(const FString& msg);
	// donghyun : 소켓 닫는 함수
	void closeConnect();

	// donghyun : 아래 함수들은 모두 클라에서 서버로 보낼
	// 메세지들을 각 명령어 형태로 포맷팅해주는 함수
	const FString FormatLoginComm(const FString& Nickname);
	const FString FormatShowPlayerListComm();
	const FString FormatShowRoomListComm();
	const FString FormatShowPlayerInfoComm(const FString& Nickname);
	const FString FormatShowRoomInfoComm(const FString& RoomNum);
	const FString FormatMakeRoomComm(const FString& RoomMaximumCnt, const FString& RoomName);
	const FString FormatQuitChattingRoomComm();
	const FString FormatJoinRoomComm(const FString& RoomNum);
	const FString FormatWhisperComm(const FString& PlayerName, const FString& Msg);
	const FString QuitProgramComm();
};
