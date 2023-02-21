// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "CCPlayerState.generated.h"


UENUM(BlueprintType)
enum class EPlayerState : uint8
{
	Connected UMETA(Displayname = "Connected"),
	Login UMETA(Displayname = "Login"),
	Chatting UMETA(Displayname = "Chatting")
};

/**
 * 
 */
UCLASS()
class CHATTINGCLIENT_API ACCPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	EPlayerState PlayerState = EPlayerState::Connected;

	ACCPlayerState();
};
