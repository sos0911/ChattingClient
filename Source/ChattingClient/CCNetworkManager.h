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
	// donghyun : ���� ����
	UCCNetworkManager();
	void Initialize(const FString& ServerIP_Str, const FString& Port);
	// donghyun : ������ �޼��� ������ �Լ�
	// �ڳ��� ������ '\r\n'�� ������ �ڿ� ���̹Ƿ�
	// �̰� �ٿ��� ������ ���� ����
	void sendMsg(const FString& msg);
	// donghyun : �������� �޼��� �޴� �Լ�
	void RecvMsg();
	// donghyun : �޼��� ������ �����ؼ� �帧 �Ѱ��ִ� �Լ�
	void JudgePacket(const FString& msg);
	// donghyun : ���� �ݴ� �Լ�
	void closeConnect();

	// donghyun : �Ʒ� �Լ����� ��� Ŭ�󿡼� ������ ����
	// �޼������� �� ��ɾ� ���·� ���������ִ� �Լ�
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
