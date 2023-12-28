// Fill out your copyright notice in the Description page of Project Settings.


#include "BBC.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h" //���� �Է��� ����ϱ� ���� �߰�
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABBC::ABBC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);	

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	//ĳ���� �ʱ� ��ġ�� ����
	GetMesh()->SetRelativeLocation(FVector(0, 0, -GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));
	//ĳ���� �ʱ� ȸ����(Pitch,Yaw,Roll)
	GetMesh()->SetRelativeRotation(FRotator(0, -90.0f, 0));

}


// Called when the game starts or when spawned
void ABBC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABBC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input

// �Ʒ��� �Լ��� ���ؼ� �÷��̾� �Է� ��ҿ� �Է� ���ε��� ����.
void ABBC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// ����ȯ�� ���ؼ� PlayerInputComponent �� UEnhancedInputComponent ������ ĳ����.
	// ��, ���� �Է� ����� �����ϴ� Ŀ���� �Է� ������Ʈ Ŭ������ UEnhancedInputComponent�� ĳ����.
	
	UEnhancedInputComponent* UEIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (UEIC)
	{
		// ��ӹ��� ACharacter �� Jump ������ �Լ��� �̹� �ֱ� ������ ABBC::Jump �Լ��� ������ �ʾƵ� �ȴ�.
		// �Ʒ�ó�� �츮�� ���� �׼ǿ� ���ε��� �ɾ��ְ� ȣ���Ű�� �ڵ带 �ۼ�.
		UEIC->BindAction(IA_Jump, ETriggerEvent::Started, this, &ABBC::Jump);
		UEIC->BindAction(IA_Jump, ETriggerEvent::Completed, this, &ABBC::StopJumping);

		UEIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ABBC::Move);
		UEIC->BindAction(IA_Look, ETriggerEvent::Triggered, this, &ABBC::Look);
	}
}


void ABBC::Move(const FInputActionValue& Value)
{
	//�Է� �� Valu�� ���� 2��(X,Y)������ ���� ����.
	FVector2D Dir = Value.Get<FVector2D>();

	//���� ��Ʈ�ѷ��� ȸ�� ���� �����ͼ� �̸� Yaw ���� ����� ĳ���Ͱ� �ٶ󺸴� ������ ���Ѵ�.
	//��, Yaw�� �ش��ϴ� �� �ܿ��� 0�� ���� ������ Yaw������ ���ϱ� ���ؼ��̴�.
	FRotator CameraRotaion = GetControlRotation();
	FRotator DirectionRotation = FRotator(0, CameraRotaion.Yaw, 0);

	//���� ������ ���� �������� ĳ���Ͱ� �����ϴ� ������ ���Ͱ��� ���������� �̵��ϴ� ���Ͱ��� ���ϰԵȴ�.
	FVector FowardVector = UKismetMathLibrary::GetForwardVector(DirectionRotation);
	FVector RightVector = UKismetMathLibrary::GetRightVector(DirectionRotation);

	//���������� ���� ������ ���Ϳ� ���� �̵� �Է� Dir.Y �� ���ؼ� �̵����� �߰����ش�.
	//�ι�° �ڵ�� ���� ������ ���Ϳ� �¿� �̵� �Է� Dir.X�� ���ؼ� �̵����� �߰����ش�.

	AddMovementInput(FowardVector, Dir.Y);
	AddMovementInput(RightVector, Dir.X);
}

void ABBC::Look(const FInputActionValue& Value)
{
	//��ó�� �̹����� ĳ������ ȸ���� ���ؼ� �Է� ������ ���� ���� �����Ѵ�.
	FVector2D Rotation = Value.Get<FVector2D>();

	//���Ŀ� �Ʒ�ó�� Yaw�� ����, Pitch�� ���� �̵����� �����Ѵ�.
	AddControllerYawInput(Rotation.X);
	AddControllerPitchInput(Rotation.Y);
}


