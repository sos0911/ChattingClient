// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
//#include "UW_Login.h"
#include "CCPlayerState.h"

#include "CCPlayerController.generated.h"


class UUW_Login;
class UUW_WaitRoom;
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

	// donghyun : 여기서부터는 서버로부터 받아온 쿼리에 대한 처리
	void SetConntectedUI();
	void SetLoginUI();
	

private:
	TSubclassOf<UUW_Login> LoginUIClass;
	TSubclassOf<UUW_WaitRoom> WaitRoomUIClass;

	UUW_Login* LoginUIObject;
	UUW_WaitRoom* WaitRoomUIObject;
	UCCNetworkManager* NetworkManagerPtr;
	ACCPlayerState* CCPlayerStatePtr;
};
