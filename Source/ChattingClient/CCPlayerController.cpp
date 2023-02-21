// Fill out your copyright notice in the Description page of Project Settings.

#include "CCPlayerController.h"
#include "UW_Login.h"
#include "CCNetworkManager.h"

ACCPlayerController::ACCPlayerController()
{
	static ConstructorHelpers::FClassFinder<UUW_Login> WB_Login(TEXT(\
		"/Game/UI/BP_Login"));
	if (WB_Login.Succeeded())
	{
		LoginUIClass = WB_Login.Class;
	}
}

void ACCPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (LoginUIClass)
	{
		LoginUIObject = CreateWidget<UUW_Login>(GetWorld(), LoginUIClass);
		if (LoginUIObject)
		{
			LoginUIObject->AddToViewport();
		}
	}

	NetworkManagerPtr = Cast<UCCNetworkManager>(\
		UGameplayStatics::GetGameInstance(GetWorld()));
	if (!NetworkManagerPtr)
	{
		UE_LOG(LogTemp, Warning, TEXT("networkmanager is null pointer"));
	}
}

//void ACCPlayerController::SetupInputComponent()
//{
//	Super::SetupInputComponent();
//}

void ACCPlayerController::PlayerTick(float Deltatime)
{
	NetworkManagerPtr->RecvMsg();
}

void ACCPlayerController::Login()
{
	
}