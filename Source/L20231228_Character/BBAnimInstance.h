// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BBAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class L20231228_CHARACTER_API UBBAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	//�� �ڵ�� ���Ͽ� UAnimInstance���� ���Ǵµ� �ٽ��� NativeUpdateAnimation �Լ��� ������.
	// �� �Լ��� �̿��ؼ� �ִϸ��̼��� �����Ӹ���(Tick����) ȣ���ؼ� ������Ʈ.
	// ���� ���� �۾� ���п� �츮�� ����� �ε巴�� ���°��� ����.
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;


	//ĳ������ �̵��ӵ��� ��� ���� ���� ����
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Stat")
	float Speed;
};
