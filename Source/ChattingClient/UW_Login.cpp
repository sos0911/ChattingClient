// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_Login.h"
#include "Kismet/GameplayStatics.h"

void UUW_Login::SummitButtonCallback()
{
	
	if (NetworkManager)
	{
		/*int Itemnumber = 2;
		TMap<FString, FStringFormatArg> args;
		args.Emplace(Input_IP->GetText().ToString(), \
			Input_Port->GetText().ToString());
		FString msg = FString::Format(TEXT("o {} {}"), args);*/
		FString msg = FString::Printf(TEXT("o %s %s"), *(Input_IP->GetText().ToString()), \
			*(Input_Port->GetText().ToString()));
		
		NetworkManager->Initialize(Input_IP->GetText().ToString(), Input_Port->GetText().ToString());
		NetworkManager->sendMsg(msg);
	}
}

void UUW_Login::NativeConstruct()
{
	if (Button_Submit)
	{
		Button_Submit->OnClicked.AddDynamic(this, &UUW_Login::SummitButtonCallback);
	}
	NetworkManager = Cast<UCCNetworkManager>(\
		UGameplayStatics::GetGameInstance(GetWorld()));
	if (!NetworkManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("networkmanager is null pointer"));
	}
}
