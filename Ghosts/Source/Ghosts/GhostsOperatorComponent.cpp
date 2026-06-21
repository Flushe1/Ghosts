// Copyright Epic Games, Inc. All Rights Reserved.

#include "GhostsOperatorComponent.h"

UGhostsOperatorComponent::UGhostsOperatorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGhostsOperatorComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	Stamina = MaxStamina;
	Suppression = FMath::Clamp(Suppression, 0.0f, 1.0f);

	OnHealthChanged.Broadcast(Health, MaxHealth);
	OnStaminaChanged.Broadcast(Stamina, MaxStamina);
	OnSuppressionChanged.Broadcast(Suppression);
}

void UGhostsOperatorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Stamina < MaxStamina)
	{
		Stamina = FMath::Min(MaxStamina, Stamina + StaminaRecoveryPerSecond * DeltaTime);
		OnStaminaChanged.Broadcast(Stamina, MaxStamina);
	}

	if (Suppression > 0.0f)
	{
		Suppression = FMath::Max(0.0f, Suppression - SuppressionRecoveryPerSecond * DeltaTime);
		OnSuppressionChanged.Broadcast(Suppression);
	}
}

void UGhostsOperatorComponent::ApplyDamage(float DamageAmount)
{
	if (DamageAmount <= 0.0f || !IsAlive())
	{
		return;
	}

	Health = FMath::Max(0.0f, Health - DamageAmount);
	OnHealthChanged.Broadcast(Health, MaxHealth);
}

void UGhostsOperatorComponent::RestoreHealth(float HealAmount)
{
	if (HealAmount <= 0.0f || !IsAlive())
	{
		return;
	}

	Health = FMath::Min(MaxHealth, Health + HealAmount);
	OnHealthChanged.Broadcast(Health, MaxHealth);
}

bool UGhostsOperatorComponent::ConsumeStamina(float StaminaAmount)
{
	if (StaminaAmount <= 0.0f)
	{
		return true;
	}

	if (Stamina < StaminaAmount)
	{
		return false;
	}

	Stamina -= StaminaAmount;
	OnStaminaChanged.Broadcast(Stamina, MaxStamina);
	return true;
}

void UGhostsOperatorComponent::AddSuppression(float SuppressionAmount)
{
	if (SuppressionAmount <= 0.0f)
	{
		return;
	}

	Suppression = FMath::Clamp(Suppression + SuppressionAmount, 0.0f, 1.0f);
	OnSuppressionChanged.Broadcast(Suppression);
}
