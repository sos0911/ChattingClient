// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"

#include "CCPlayerState.generated.h"

class APlayerState;

// donghyun : player의 status로 사용하기 위한 enum class
// 서버에서 명령어가 들어올 때 이걸로 로직 분리
UENUM(BlueprintType)
enum class EPlayerState : uint8
{
	UnConnected UMETA(Displayname = "UnConnected"),
	Connected UMETA(Displayname = "Connected"),
	Login UMETA(Displayname = "Login"),
	Chatting UMETA(Displayname = "Chatting"),
	ShowPlayerListCommSent UMETA(Displayname = "ShowPlayerListCommSent"),
	ShowRoomListCommSent UMETA(Displayname = "ShowRoomListCommSent"),
	ShowPlayerInfoCommSent UMETA(Displayname = "ShowPlayerInfoCommSent"),
	ShowRoomInfoCommSent UMETA(Displayname = "ShowRoomInfoCommSent"),
	JoinRoomCommSent UMETA(Displayname = "JoinRoomCommSent"),
	MakeRoomCommSent UMETA(Displayname = "MakeRoomCommSent"),
};

/**
 * 
 */
UCLASS()
class CHATTINGCLIENT_API ACCPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	EPlayerState EnumPlayerState;
	EPlayerState BefEnumPlayerState;

	ACCPlayerState();
};
