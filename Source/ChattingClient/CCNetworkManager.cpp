// Fill out your copyright notice in the Description page of Project Settings.


#include "CCNetworkManager.h"

void UCCNetworkManager::Shutdown()
{
	socket->Close();
	ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(socket);
}

UCCNetworkManager::UCCNetworkManager()
{
	socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->\
		CreateSocket(NAME_Stream, TEXT("default"), false);
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