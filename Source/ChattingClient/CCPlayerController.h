// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
//#include "UW_Login.h"

#include "CCPlayerController.generated.h"


class UUW_Login;
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

	// donghyun : ���⼭���ʹ� �����κ��� �޾ƿ� ������ ���� ó��
	void Login();
	

private:
	TSubclassOf<UUW_Login> LoginUIClass;
	UUW_Login* LoginUIObject;
	UCCNetworkManager* NetworkManagerPtr;
};
