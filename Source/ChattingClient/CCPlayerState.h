// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "CCPlayerState.generated.h"


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
};

/**
 * 
 */
UCLASS()
class CHATTINGCLIENT_API ACCPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	EPlayerState EnumPlayerState = EPlayerState::UnConnected;
	EPlayerState BefEnumPlayerState = EPlayerState::UnConnected;

	ACCPlayerState();
};
