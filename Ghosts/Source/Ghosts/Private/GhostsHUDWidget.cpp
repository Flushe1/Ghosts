// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/GhostsHUDWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void UGhostsHUDWidget::NativeConstruct()
{
    Super::NativeConstruct();
    // Estado inicial ao criar o widget
    UpdateAmmo(30, 90);
}

void UGhostsHUDWidget::UpdateAmmo(int32 RoundsInMagazine, int32 ReserveRounds)
{
    if (!AmmoText) return;

    FString AmmoString = FString::Printf(TEXT("%d / %d"), RoundsInMagazine, ReserveRounds);
    AmmoText->SetText(FText::FromString(AmmoString));
}

void UGhostsHUDWidget::UpdateHealth(float CurrentHealth, float MaxHealth)
{
    if (!HealthBar || !HealthText) return;

    float Percent = (MaxHealth > 0.f) ? CurrentHealth / MaxHealth : 0.f;
    HealthBar->SetPercent(Percent);

    FString HealthString = FString::Printf(TEXT("%.0f / %.0f"), CurrentHealth, MaxHealth);
    HealthText->SetText(FText::FromString(HealthString));
}