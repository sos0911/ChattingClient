// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "UW_MakeRoomPopup.generated.h"

class UEditableTextBox;
class UButton;
class UScrollBox;

class UCCNetworkManager;

/**
 *
 */
UCLASS()
class CHATTINGCLIENT_API UUW_MakeRoomPopup : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(Meta = (BindWidget))
		UScrollBox* ScrollBox_Result;
	UPROPERTY(Meta = (BindWidget))
		UEditableTextBox* Input_RoomName;
	UPROPERTY(Meta = (BindWidget))
		UEditableTextBox* Input_RoomMaximumCnt;
	UPROPERTY(Meta = (BindWidget))
		UButton* Button_Confirm;
	UPROPERTY(Meta = (BindWidget))
		UButton* Button_Exit;


	UFUNCTION(BlueprintCallable)
		void MakeRoomButtonCallback();
	UFUNCTION(BlueprintCallable)
		void MakeRoomExitCallback();

	UFUNCTION(BlueprintCallable)
		class ACCPlayerController* GetPlayerController();

	UCCNetworkManager* NetworkManager;

protected:
	virtual void NativeConstruct() override;
public:
	// donghyun : 채팅방 관련 UI 갱신 함수
	void SetMakeRoomResultUI(const FString& msg);
};