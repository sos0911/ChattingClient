// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EQueryFlag
{
	MakeRoom UMETA(Displayname = "MakeRoom"),
	JoinRoom UMETA(Displayname = "JoinRoom"),
	RenewPlayerList UMETA(Displayname = "RenewPlayerList"),
	RenewRoomList UMETA(Displayname = "RenewRoomList"),
	ViewRoomInfo UMETA(Displayname = "ViewRoomInfo"),
	ViewPlayerInfo UMETA(Displayname = "ViewPlayerInfo"),
	SendWhisper UMETA(Displayname = "SendWhisper"),
};

constexpr int RECVBUFSIZE = 1024;

// donghyun : �Ʒ� msg���� ������ ���� �޼����� �Ϻκ��� �� ����
extern FString LoginSuccessMsg = "�α��� �Ͽ����ϴ�.";
extern FString LoginFailMsg = "�ش� �̸��� ����� �� �����ϴ�";

//��ȭ���� �����Ǿ����ϴ�.
//�ڱ� �ڽſ��Դ� ���� �� �����ϴ�.
//���� ����
//������ ���½��ϴ�
//���� ã�� �� �����ϴ�.
//�������� �ʴ� ��ȭ���Դϴ�.
//���� ã�� �� �����ϴ�.
//���� ���� �� ä�ù濡 �ֽ��ϴ�.
//���� ���� ���ǿ� �ֽ��ϴ�.
//�� ���� �������� �ʴ� ��ȭ���Դϴ�.
//�� �ο� �ʰ��� ������ �Ұ����մϴ�.
//���� �����̽��ϴ�.
//���� �����̽��ϴ�.
//ä�ù濡�� ���Խ��ϴ�.
