// Copyright Epic Games, Inc. All Rights Reserved.

#include "GhostsFirearmComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

UGhostsFirearmComponent::UGhostsFirearmComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UGhostsFirearmComponent::BeginPlay()
{
	Super::BeginPlay();

	RoundsInMagazine = MagazineCapacity;
	ReserveRounds = StartingReserveRounds;

	OnAmmoChanged.Broadcast(RoundsInMagazine, ReserveRounds);
	OnFireModeChanged.Broadcast(FireMode);
}

bool UGhostsFirearmComponent::StartTriggerPull()
{
	bTriggerHeld = true;

	if (FireMode == EGhostsFireMode::Burst)
	{
		BurstShotsRemaining = BurstCount;
	}

	return TryFire();
}

void UGhostsFirearmComponent::StopTriggerPull()
{
	bTriggerHeld = false;
	BurstShotsRemaining = 0;
}

bool UGhostsFirearmComponent::TryFire()
{
	if (!CanFire())
	{
		if (!bReloading && RoundsInMagazine <= 0)
		{
			OnDryFired.Broadcast();
		}

		return false;
	}

	--RoundsInMagazine;
	bShotCooldown = true;

	OnFired.Broadcast();
	OnAmmoChanged.Broadcast(RoundsInMagazine, ReserveRounds);

	GetWorld()->GetTimerManager().SetTimer(ShotCooldownTimer, this, &UGhostsFirearmComponent::ClearShotCooldown, SecondsBetweenShots, false);
	return true;
}

bool UGhostsFirearmComponent::BeginReload()
{
	if (bReloading || RoundsInMagazine >= MagazineCapacity || ReserveRounds <= 0)
	{
		return false;
	}

	bReloading = true;
	bTriggerHeld = false;
	BurstShotsRemaining = 0;

	OnReloadStarted.Broadcast();
	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &UGhostsFirearmComponent::FinishReload, ReloadTime, false);
	return true;
}

void UGhostsFirearmComponent::FinishReload()
{
	if (!bReloading)
	{
		return;
	}

	const int32 RoundsNeeded = MagazineCapacity - RoundsInMagazine;
	const int32 RoundsToLoad = FMath::Min(RoundsNeeded, ReserveRounds);

	RoundsInMagazine += RoundsToLoad;
	ReserveRounds -= RoundsToLoad;
	bReloading = false;

	OnReloadFinished.Broadcast();
	OnAmmoChanged.Broadcast(RoundsInMagazine, ReserveRounds);
}

void UGhostsFirearmComponent::SetFireMode(EGhostsFireMode NewFireMode)
{
	if (FireMode == NewFireMode)
	{
		return;
	}

	FireMode = NewFireMode;
	BurstShotsRemaining = 0;
	OnFireModeChanged.Broadcast(FireMode);
}

bool UGhostsFirearmComponent::CanFire() const
{
	return FireMode != EGhostsFireMode::Safe && !bReloading && !bShotCooldown && RoundsInMagazine > 0;
}

void UGhostsFirearmComponent::ClearShotCooldown()
{
	bShotCooldown = false;
	ContinueAutomaticFire();
}

void UGhostsFirearmComponent::ContinueAutomaticFire()
{
	if (FireMode == EGhostsFireMode::FullAuto && bTriggerHeld)
	{
		TryFire();
		return;
	}

	if (FireMode == EGhostsFireMode::Burst && bTriggerHeld)
	{
		--BurstShotsRemaining;

		if (BurstShotsRemaining > 0)
		{
			TryFire();
		}
	}
}
