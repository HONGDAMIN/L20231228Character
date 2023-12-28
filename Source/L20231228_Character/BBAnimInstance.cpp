// Fill out your copyright notice in the Description page of Project Settings.


#include "BBAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UBBAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	//Super�� �θ� �Լ��� ȣ���ؼ� ������ �ϱ� ���� �۾�.
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	//�ش� ���� �����ڰ� ���� Owner�� �´��� �����ͼ� ���� �Ŀ� �۾��� �Ѵ�.
	ACharacter* MyCharacter = Cast<ACharacter>(TryGetPawnOwner());
	if (IsValid(MyCharacter))
	{
		//Velocity�� ������ ������ �ӵ��̸�, ��Į��� �ӵ��� ������ �ִ�.
		//�׷��� �Ʒ�ó�� �ؼ� �ӵ��� ������ ���ϵ��� ���ش�.
		// Size2D�� �ϸ� Z���� �����ϰ� �ӵ��� �����
		Speed = MyCharacter->GetCharacterMovement()->Velocity.Size2D();
	}
}
