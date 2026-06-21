// Fill out your copyright notice in the Description page of Project Settings.


#include "GhostsHealthComponent.h"

UGhostsHealthComponent::UGhostsHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

float UGhostsHealthComponent::GetCurrentHealth() const { return CurrentHealth; }
float UGhostsHealthComponent::GetMaxHealth() const { return MaxHealth; }
bool UGhostsHealthComponent::IsAlive() const { return CurrentHealth > 0.f; }

void UGhostsHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    CurrentHealth = MaxHealth;

    // Registra para receber dano do owner
    if (AActor* Owner = GetOwner())
    {
        Owner->OnTakeAnyDamage.AddDynamic(this, &UGhostsHealthComponent::OnTakeAnyDamage);
    }
}

void UGhostsHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage,
    const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    if (Damage <= 0.f || !IsAlive()) return;

    CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.f, MaxHealth);

    OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);

    if (CurrentHealth <= 0.f)
    {
        OnDeath.Broadcast();
    }
}

void UGhostsHealthComponent::ApplyDamage(float DamageAmount)
{
    if (DamageAmount <= 0.f || !IsAlive()) return;

    CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.f, MaxHealth);
    OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);

    if (CurrentHealth <= 0.f)
    {
        OnDeath.Broadcast();
    }
}