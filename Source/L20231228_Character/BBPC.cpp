// Fill out your copyright notice in the Description page of Project Settings.


#include "BBPC.h"
#include "EnhancedInputSubsystems.h"

void ABBPC::BeginPlay()
{
	Super::BeginPlay();

	//�Ʒ��� �ڵ�� Subsystem ���κ��� Localplayer ������ �������� �ڵ�.
	//ULocalPlayer Ŭ�������� ����ý����� �����ͼ� �̰����� ���� �����÷��̾� ������ �����´�.

	UEnhancedInputLocalPlayerSubsystem* SubSystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	//���� ���� ����ý����� ��ȿ�ϰ�, DefaultIMC�� ��ȿ�� ��쿡 ������ �̾��.
	if (SubSystem && DefaultIMC)
	{
		//MappingContext�� DefaultIMC�� ���� �ý��ۿ� �߰��Ѵ�.
		// ���� �̸� ���� �Է� ������ ȿ�������� �����ϰ� �����ϰ� �Ǹ�, 0�� ���ؽ�Ʈ�� �켱����.
		//�̴� �� ���� �켱������ ���ؽ�Ʈ�� ���� Ȱ��ȭ�� ��쿡�� �ش� ���ؽ�Ʈ�� ����ϰ� �Ѵ�.
		SubSystem->AddMappingContext(DefaultIMC, 0);
	}
}
