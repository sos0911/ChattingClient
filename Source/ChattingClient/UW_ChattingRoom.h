// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/ScrollBox.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "Runtime/UMG/Public/Components/EditableTextBox.h"

#include "UW_ChattingRoom.generated.h"

class UCCNetworkManager;

/**
 *
 */
UCLASS()
class CHATTINGCLIENT_API UUW_ChattingRoom : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(Meta = (BindWidget))
		UScrollBox* ScrollBox_Chat;

	UPROPERTY(Meta = (BindWidget))
		UEditableTextBox* Input_Chat;

	UPROPERTY(Meta = (BindWidget))
		UButton* Button_Exit;


	UFUNCTION(BlueprintCallable)
		void RoomExitCallback();
	UFUNCTION(BlueprintCallable)
		void SendChattingCallback(const FText& Text, ETextCommit::Type CommitMethod);

	UFUNCTION(BlueprintCallable)
		class ACCPlayerController* GetPlayerController();

	UCCNetworkManager* NetworkManager;

protected:
	virtual void NativeConstruct();

public:
	void RenewChattingRoomLog(const FString& msg);
};


