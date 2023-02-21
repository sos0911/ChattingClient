// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Runtime/Networking/Public/Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
//#include "/Engine/Source/Runtime/Sockets/Public/SocketSubsystem.h"


#include "CCNetworkManager.generated.h" 

class ACCPlayerController;

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
	// 서버 입장에서는 텔넷이 보낼때 '\r\n'을 무조건 뒤에 붙이므로
	// 이거 붙여서 보내야 통일 가능
	void sendMsg(const FString& msg);
	void RecvMsg();
	// donghyun : 메세지 받은거 구분해서 흐름 넘겨주는 함수
	void JudgePacket(const FString& msg);
	void Init() override;

	const FString FormatLoginComm(const FString& Nickname);
	//FString KoreanToFString(const FString& InKoreanText);
};
