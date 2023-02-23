// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "UW_JoinRoomPopup.generated.h"

class UScrollBox;
class UEditableTextBox;
class UButton;

class UCCNetworkManager;

/**
 *
 */
UCLASS()
class CHATTINGCLIENT_API UUW_JoinRoomPopup : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(Meta = (BindWidget))
		UScrollBox* ScrollBox_Result;
	UPROPERTY(Meta = (BindWidget))
		UEditableTextBox* Input_RoomNum;
	UPROPERTY(Meta = (BindWidget))
		UButton* Button_Confirm;
	UPROPERTY(Meta = (BindWidget))
		UButton* Button_Exit;


	UFUNCTION(BlueprintCallable)
		void JoinRoomButtonCallback();
	UFUNCTION(BlueprintCallable)
		void JoinRoomExitCallback();

	UFUNCTION(BlueprintCallable)
		class ACCPlayerController* GetPlayerController();

	UCCNetworkManager* NetworkManager;

protected:
	virtual void NativeConstruct() override;
public:
	// donghyun : 채팅방 관련 UI 갱신 함수
	void SetJoinRoomResultUI(const FString& msg);
};