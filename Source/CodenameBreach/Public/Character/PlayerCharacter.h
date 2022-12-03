// Copyright 2017-2022 Wabbit, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CodenameBreach/BreachTypes/TurningInPlace.h"
#include "Interfaces/InteractWithCrosshairsInterface.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UWidgetComponent;
class AWeapon;
class UCombatComponent;
class UAnimMontage;

UCLASS()
class CODENAMEBREACH_API APlayerCharacter : public ACharacter, public IInteractWithCrosshairsInterface
{
	GENERATED_BODY()

public:
	APlayerCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PostInitializeComponents() override;
	void PlayFireMontage(bool bAiming);

	UPROPERTY(EditAnywhere, Category = "WeaponRotationCorrection")
	float RightHandRotationRoll = 180.f;

	UPROPERTY(EditAnywhere, Category = "WeaponRotationCorrection")
	float RightHandRotationYaw;
	
	UPROPERTY(EditAnywhere, Category = "WeaponRotationCorrection")
	float RightHandRotationPitch;

protected:
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	void EquipButtonPressed();
	void CrouchButtonPressed();
	void AimButtonPressed();
	void AimButtonReleased();
	void FireButtonPressed();
	void FireButtonReleased();
	void AimOffset(float DeltaTime);
	virtual void Jump() override;

private:

	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* OverheadWidget;

	UPROPERTY(ReplicatedUsing = OnRep_OverlappingWeapon)
	AWeapon* OverlappingWeapon;

	UFUNCTION()
	void OnRep_OverlappingWeapon(AWeapon* LastWeapon);
	
	UPROPERTY(VisibleAnywhere)
	UCombatComponent* Combat;

	UFUNCTION(Server, Reliable)
	void ServerEquipButtonPressed();

	float AO_Yaw;
	float InterpAO_Yaw;
	float AO_Pitch;
	FRotator StartingAimRotation;

	ETurningInPlace TurningInPlace;
	void TurnInPlace(float DeltaTime);

	UPROPERTY(EditAnywhere, Category = Combat)
	UAnimMontage* FireWeaponMontage;

	void HideCameraIfCharacterClose();

	UPROPERTY(EditAnywhere)
	float CameraThreshold = 200.f;

public:	
	//Getters
	bool bIsAiming();
	bool bIsWeaponEquipped();
	AWeapon* GetEquippedWeapon();
	FVector GetHitTarget() const;
	FORCEINLINE float GetAO_Yaw() const{ return AO_Yaw; }
	FORCEINLINE float GetAO_Pitch() const { return AO_Pitch; }
	FORCEINLINE ETurningInPlace GetTurningInPlace() const { return TurningInPlace;  }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	//Setters
	void SetOverlappingWeapon(AWeapon* Weapon);

};
