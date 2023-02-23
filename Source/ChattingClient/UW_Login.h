// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "UW_Login.generated.h"

class UScrollBox;
class UEditableTextBox;
class UButton;
class UTextBlock;
class UCCNetworkManager;

/**
 * 
 */
UCLASS()
class CHATTINGCLIENT_API UUW_Login : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(Meta = (BindWidget))
		UEditableTextBox* Input_Nickname;
	UPROPERTY(Meta = (BindWidget))
		UEditableTextBox* Input_IP;
	UPROPERTY(Meta = (BindWidget))
		UEditableTextBox* Input_Port;
	UPROPERTY(Meta = (BindWidget))
		UButton* Button_Submit;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* Text_Nickname;
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* Text_IP;
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* Text_Port;
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* Text_Notify;

	UFUNCTION(BlueprintCallable)
		void SummitButtonCallback();
	UFUNCTION(BlueprintCallable)
		class ACCPlayerController* GetPlayerController();
	
	UCCNetworkManager* NetworkManager;

protected:
	virtual void NativeConstruct() override;
public:
	// donghyun : 로그인 UI 갱신 함수
	void SetConnectedUI();
	// donghyun : 로그인 관련 이슈 갱신 함수
	void SetLoginNotifyUI(const FString& msg);
};
