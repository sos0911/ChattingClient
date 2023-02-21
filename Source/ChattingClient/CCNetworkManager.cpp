// Fill out your copyright notice in the Description page of Project Settings.

#include "FServerProtocol.h"
#include "CCNetworkManager.h"
#include "Windows/AllowWindowsPlatformTypes.h"
#include "CCPlayerController.h"


void UCCNetworkManager::Shutdown()
{
	socket->Close();
	ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(socket);
}

UCCNetworkManager::UCCNetworkManager()
{
	socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->\
		CreateSocket(NAME_Stream, TEXT("default"), false);
	// donghyun : 논블로킹 설정 및 nagle 알고리즘 꺼주기(텔넷과 유사한 환경 조성)
	socket->SetNonBlocking();
	socket->SetNoDelay();

	EncodedBuf = "";

	// donghyun : 플레이어 컨트롤러 캐싱
	PlayerController =  Cast<ACCPlayerController>(GetWorld()->GetFirstPlayerController());
}

void UCCNetworkManager::Initialize(const FString& ServerIP_Str, const FString& Port)
{
	int32 Port_Int = FCString::Atoi(*Port);
	TSharedPtr<FInternetAddr> ServerIP_Ptr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	bool IsValid = true;
	ServerIP_Ptr->SetIp(*ServerIP_Str, IsValid);
	ServerIP_Ptr->SetPort(Port_Int);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("connecting..")));

	if (IsValid)
	{
		if (socket->Connect(*ServerIP_Ptr))
		{
			UE_LOG(LogTemp, Warning, TEXT("connected to server"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("falied to connect server"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("invalid address"));
	}
}

void UCCNetworkManager::sendMsg(const FString& msg)
{
	TArray<uint8> Msg_Bytes;
	FTCHARToUTF8 Converter(*msg);
	Msg_Bytes.Append((uint8*)Converter.Get(), Converter.Length());

	int32 ByteSent = 0;
	bool IsSended = socket->Send(Msg_Bytes.GetData(), Msg_Bytes.Num(), ByteSent);
	
	if (IsSended)
	{
		UE_LOG(LogTemp, Warning, TEXT("Sent message: %s"), *msg);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to send msg"));
	}
}

void UCCNetworkManager::RecvMsg()
{
	if (!socket)
	{
		return;
	}

	char buf[RECVBUFSIZE] = { NULL, };
	int32 bytesSents = 0;
	FString encode;

	bool returnValue = socket->Recv((uint8*)(buf), RECVBUFSIZE- 1, bytesSents);
	if (!returnValue)
	{
		return;
	}
	if (0 == bytesSents)
	{
		return;
	}

	wchar_t encodebuf[RECVBUFSIZE] = { NULL, };
	int32 len = MultiByteToWideChar(CP_ACP, 0, buf, strlen(buf), NULL, NULL);
	MultiByteToWideChar(CP_ACP, 0, buf, strlen(buf), encodebuf, len);

	for (int32 i = 0; i <= len; ++i)
	{
		if (encodebuf[i] == '\0')
		{
			JudgePacket(EncodedBuf);
			EncodedBuf = "";
		}
		else
		{
			EncodedBuf += encodebuf[i];
		}
	}
}

void UCCNetworkManager::JudgePacket(const FString& msg)
{
	if (msg.Contains(FString(LoginSuccessMsg)))
	{
		PlayerController->Login();
	}
}

