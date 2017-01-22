// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "GGJPlayer.generated.h"

UCLASS()
class GGJ17ALPHA_API AGGJPlayer : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(Category=Camera, EditAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(Category = Camera, EditAnywhere)
	USpringArmComponent *SpringArm;

	UPROPERTY(Category = Mesh, EditAnywhere)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(Category=Stamina, EditAnywhere)
	float Stamina;
	
	UPROPERTY(Category=Stamina, VisibleAnywhere)
	float MaxStamina;

	UPROPERTY(Category = Stamina, EditAnywhere)
	bool bUsingSpecial;

	UPROPERTY(Category = Movement, EditAnywhere)
	float MovementSpeed;

	FVector2D MovementInput;
	FVector2D CameraInput;

public:

	// Sets default values for this character's properties
	AGGJPlayer();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float value);
	void MoveRight(float value);
	void CameraPitch(float value);
	void CameraYaw(float value);

	UFUNCTION(BlueprintCallable, Category=Stamina)
	float GetStamina();

	UFUNCTION(BlueprintCallable, Category = Stamina)
	float GetMaxStamina();

	UFUNCTION(BlueprintCallable, Category = Stamina)
	float GetStaminaPercent();

	UFUNCTION(BlueprintCallable, Category = Stamina)
	void IncreaseStamina(float value);

	UFUNCTION(BlueprintCallable, Category = Stamina)
	void DecreaseStamina(float value);

	UFUNCTION(BlueprintCallable, Category = Stamina)
	bool IsUsingSpecial();

	UFUNCTION(BlueprintCallable, Category = Stamina)
	void EnableSpecial(bool value);

	UFUNCTION(BlueprintCallable, Category = Movement)
	float GetMovementSpeed();

};
