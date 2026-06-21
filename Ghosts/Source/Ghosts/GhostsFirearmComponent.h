// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GhostsFirearmComponent.generated.h"

UENUM(BlueprintType)
enum class EGhostsFireMode : uint8
{
	Safe,
	SemiAuto,
	Burst,
	FullAuto
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGhostsFirearmSimpleEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGhostsAmmoChanged, int32, RoundsInMagazine, int32, ReserveRounds);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGhostsFireModeChanged, EGhostsFireMode, FireMode);

UCLASS(ClassGroup=(Ghosts), meta=(BlueprintSpawnableComponent))
class GHOSTS_API UGhostsFirearmComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UGhostsFirearmComponent();

	UPROPERTY(BlueprintAssignable, Category="Firearm")
	FGhostsFirearmSimpleEvent OnFired;

	UPROPERTY(BlueprintAssignable, Category="Firearm")
	FGhostsFirearmSimpleEvent OnDryFired;

	UPROPERTY(BlueprintAssignable, Category="Firearm")
	FGhostsFirearmSimpleEvent OnReloadStarted;

	UPROPERTY(BlueprintAssignable, Category="Firearm")
	FGhostsFirearmSimpleEvent OnReloadFinished;

	UPROPERTY(BlueprintAssignable, Category="Firearm")
	FGhostsAmmoChanged OnAmmoChanged;

	UPROPERTY(BlueprintAssignable, Category="Firearm")
	FGhostsFireModeChanged OnFireModeChanged;

	UFUNCTION(BlueprintCallable, Category="Firearm")
	bool StartTriggerPull();

	UFUNCTION(BlueprintCallable, Category="Firearm")
	void StopTriggerPull();

	UFUNCTION(BlueprintCallable, Category="Firearm")
	bool TryFire();

	UFUNCTION(BlueprintCallable, Category="Firearm")
	bool BeginReload();

	UFUNCTION(BlueprintCallable, Category="Firearm")
	void FinishReload();

	UFUNCTION(BlueprintCallable, Category="Firearm")
	void SetFireMode(EGhostsFireMode NewFireMode);

	UFUNCTION(BlueprintPure, Category="Firearm")
	EGhostsFireMode GetFireMode() const { return FireMode; }

	UFUNCTION(BlueprintPure, Category="Firearm")
	int32 GetRoundsInMagazine() const { return RoundsInMagazine; }

	UFUNCTION(BlueprintPure, Category="Firearm")
	int32 GetReserveRounds() const { return ReserveRounds; }

	UFUNCTION(BlueprintPure, Category="Firearm")
	bool CanFire() const;

	UFUNCTION(BlueprintPure, Category="Firearm")
	bool IsReloading() const { return bReloading; }

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category="Firearm|Ammo", meta=(ClampMin="1"))
	int32 MagazineCapacity = 30;

	UPROPERTY(VisibleInstanceOnly, Category="Firearm|Ammo")
	int32 RoundsInMagazine = 30;

	UPROPERTY(EditDefaultsOnly, Category="Firearm|Ammo", meta=(ClampMin="0"))
	int32 StartingReserveRounds = 90;

	UPROPERTY(VisibleInstanceOnly, Category="Firearm|Ammo")
	int32 ReserveRounds = 90;

	UPROPERTY(EditDefaultsOnly, Category="Firearm|Handling", meta=(ClampMin="0.01"))
	float SecondsBetweenShots = 0.095f;

	UPROPERTY(EditDefaultsOnly, Category="Firearm|Handling", meta=(ClampMin="0.0"))
	float ReloadTime = 2.4f;

	UPROPERTY(EditDefaultsOnly, Category="Firearm|Handling", meta=(ClampMin="1"))
	int32 BurstCount = 3;

	UPROPERTY(EditDefaultsOnly, Category="Firearm|Handling")
	EGhostsFireMode FireMode = EGhostsFireMode::SemiAuto;

	bool bTriggerHeld = false;
	bool bReloading = false;
	bool bShotCooldown = false;
	int32 BurstShotsRemaining = 0;

	FTimerHandle ShotCooldownTimer;
	FTimerHandle ReloadTimer;

	void ClearShotCooldown();
	void ContinueAutomaticFire();
};
