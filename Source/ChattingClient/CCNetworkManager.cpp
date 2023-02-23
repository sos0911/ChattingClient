// Fill out your copyright notice in the Description page of Project Settings.

#include "CCNetworkManager.h"
#include "FServerProtocol.h"
#include "Windows/AllowWindowsPlatformTypes.h"
#include "CCPlayerController.h"
#include "CCPlayerState.h"
#include <string>
#include "Internationalization/Text.h"
//#include "Internationalization/TextConverter.h"
#include "Internationalization/Internationalization.h"
#include "FServerProtocol.h"

void UCCNetworkManager::Shutdown()
{
	socket->Close();
	ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(socket);
}

UCCNetworkManager::UCCNetworkManager()
{
	socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->\
		CreateSocket(NAME_Stream, TEXT("default"), false);

	EncodedBuf = "";

	// donghyun : 플레이어 컨트롤러 캐싱
	//PlayerController =  Cast<ACCPlayerController>(GetWorld()->GetFirstPlayerController());
}

void UCCNetworkManager::Initialize(const FString& ServerIP_Str, const FString& Port)
{
	if (GetWorld())
	{
		APlayerController* Temp = GetWorld()->GetFirstPlayerController();
		PlayerController = Cast<ACCPlayerController>(Temp);
		//PlayerController = Cast<ACCPlayerController>(GetWorld()->GetFirstPlayerController());
	}

	int32 Port_Int = FCString::Atoi(*Port);
	TSharedPtr<FInternetAddr> ServerIP_Ptr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	bool IsValid = true;
	ServerIP_Ptr->SetIp(*ServerIP_Str, IsValid);
	ServerIP_Ptr->SetPort(Port_Int);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("connecting..")));

	if (IsValid)
	{
		bool IsConnected = false;
		IsConnected = socket->Connect(*ServerIP_Ptr);
		if (IsConnected)
		{
			UE_LOG(LogTemp, Warning, TEXT("connected to server"));
			PlayerController->SetConntectedUI();
			PlayerController->SetPlayerState(EPlayerState::Connected);
			// donghyun : 논블로킹 설정 및 nagle 알고리즘 꺼주기(텔넷과 유사한 환경 조성)
			socket->SetNonBlocking();
			socket->SetNoDelay();

		}
		else
		{
			PlayerController->SetLoginNotifyUI(FailToConnectMsg);
			UE_LOG(LogTemp, Warning, TEXT("falied to connect server"));
		}
	}
	else
	{
		PlayerController->SetLoginNotifyUI(FailToConnectMsg);
		UE_LOG(LogTemp, Warning, TEXT("invalid address"));
	}
}

void UCCNetworkManager::sendMsg(const FString& msg)
{
	if (!socket)
	{
		return;
	}

	//packetEnd += "\n";
	char message[1024];
	const wchar_t* encode = *msg;
	char defaultSetting = '?';

	int32 len = WideCharToMultiByte(CP_ACP, 0, encode, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, encode, -1, message, len, &defaultSetting, NULL);
	int32 bytesSents = 0;

	bool IsSent = socket->Send((uint8*)(message), len, bytesSents);
	if (!IsSent)
	{
		UE_LOG(LogTemp, Warning, TEXT("send error!"));
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
	//UE_LOG(LogTemp, Warning, TEXT(msg));

	EPlayerState CurPlayerState = PlayerController->GetPlayerState();

	switch (CurPlayerState)
	{
	case EPlayerState::Connected:
	{
		if (msg.Contains(FString(LoginSuccessMsg)))
		{
			PlayerController->SetLoginUI();
			PlayerController->SetPlayerState(EPlayerState::Login);
		}
		else
		{
			PlayerController->SetLoginNotifyUI(msg);
		}
		break;
	}
	case EPlayerState::ShowPlayerListCommSent:
	{
		PlayerController->SetInfoListUI(msg);
		PlayerController->UndoPlayerState();
		break;
	}
	case EPlayerState::ShowRoomListCommSent:
	{
		PlayerController->SetInfoListUI(msg);
		PlayerController->UndoPlayerState();
		break;
	}
	case EPlayerState::ShowPlayerInfoCommSent:
	{
		PlayerController->SetPlayerInfoUI(msg);
		PlayerController->UndoPlayerState();
		break;
	}
	case EPlayerState::ShowRoomInfoCommSent:
	{
		PlayerController->SetRoomInfoUI(msg);
		PlayerController->UndoPlayerState();
		break;
	}
	case EPlayerState::Chatting:
	{
		PlayerController->RenewChattingRoomLog(msg);
		break;
	}
	case EPlayerState::JoinRoomCommSent:
	{
		if (msg.Contains(FString(JoinRoomSuccessMsg)))
		{
			PlayerController->RemoveJoinRoomPopup();
			PlayerController->WaitRoomToChattingRoom();
			PlayerController->RenewChattingRoomLog(msg);
		}
		else
		{
			PlayerController->SetJoinRoomResultUI(msg);
		}
		break;
	}
	case EPlayerState::Login:
	{
		// donghyun : 보통 귓속말이 오는 경우이다.
		PlayerController->SetWhisperUI(msg);
	}
	default:
	{
		// nothing to do
		break;
	}
	}
	
}

void UCCNetworkManager::Init()
{

}

void UCCNetworkManager::closeConnect()
{
	socket->Close();
}

const FString UCCNetworkManager::FormatLoginComm(const FString& Nickname)
{
	return FString::Printf(TEXT("login %s\n"), *Nickname);
}

const FString UCCNetworkManager::FormatShowPlayerListComm()
{
	return FString::Printf(TEXT("us\n"));
}

const FString UCCNetworkManager::FormatShowRoomListComm()
{
	return FString::Printf(TEXT("lt\n"));
}

const FString UCCNetworkManager::FormatShowPlayerInfoComm(const FString& Nickname)
{
	return FString::Printf(TEXT("pf %s\n"), *Nickname);
}

const FString UCCNetworkManager::FormatShowRoomInfoComm(const FString& RoomNum)
{
	return FString::Printf(TEXT("st %s\n"), *RoomNum);
}

const FString UCCNetworkManager::FormatMakeRoomComm(const FString& RoomMaximumCnt, const FString& RoomName)
{
	return FString::Printf(TEXT("o %s %s\n"), *RoomMaximumCnt, *RoomName);
}

const FString UCCNetworkManager::FormatQuitChattingRoomComm()
{
	return FString::Printf(TEXT("/q\n"));
}

const FString UCCNetworkManager::FormatJoinRoomComm(const FString& RoomNum)
{
	return FString::Printf(TEXT("j %s\n"), *RoomNum);
}

const FString UCCNetworkManager::FormatWhisperComm(const FString& PlayerName, const FString& Msg)
{
	return FString::Printf(TEXT("to %s %s\n"), *PlayerName, *Msg);
}

const FString UCCNetworkManager::QuitProgramComm()
{
	return FString::Printf(TEXT("x\n"));
}


//FString UCCNetworkManager::KoreanToFString(const FString& InKoreanText)
//{
//	FString OutUTF8Text;
//
//	const FTextConverter::EConversionMode ConversionMode = FTextConverter::EConversionMode::AutoDetect;
//	const FString SourceString = InKoreanText;
//	const bool bEnsureTerminated = true;
//	const TCHAR* SourcePtr = *SourceString;
//	const int32 SourceLength = FCString::Strlen(SourcePtr);
//	const ESearchCase::Type SearchCase = ESearchCase::CaseSensitive;
//	const ESearchDir::Type SearchDir = ESearchDir::FromEnd;
//	const FString ChosenCulture = FString(TEXT("ko-KR"));
//
//	FTextConverter::Convert(
//		ConversionMode,
//		SourcePtr,
//		SourceLength,
//		OutUTF8Text,
//		bEnsureTerminated,
//		SearchCase,
//		SearchDir,
//		ChosenCulture
//	);
//
//	return OutUTF8Text;
//}