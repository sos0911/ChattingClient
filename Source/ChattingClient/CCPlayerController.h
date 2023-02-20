// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UW_Login.h"

#include "CCPlayerController.generated.h"

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
	virtual void SetupInputComponent() override;
	

private:
	TSubclassOf<UUW_Login> LoginUIClass;
	UUW_Login* LoginUIObject;
};
