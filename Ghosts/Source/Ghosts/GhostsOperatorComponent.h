// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GhostsOperatorComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGhostsOperatorValueChanged, float, CurrentValue, float, MaxValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGhostsSuppressionChanged, float, CurrentSuppression);

UCLASS(ClassGroup=(Ghosts), meta=(BlueprintSpawnableComponent))
class GHOSTS_API UGhostsOperatorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UGhostsOperatorComponent();

	UPROPERTY(BlueprintAssignable, Category="Operator")
	FGhostsOperatorValueChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="Operator")
	FGhostsOperatorValueChanged OnStaminaChanged;

	UPROPERTY(BlueprintAssignable, Category="Operator")
	FGhostsSuppressionChanged OnSuppressionChanged;

	UFUNCTION(BlueprintCallable, Category="Operator")
	void ApplyDamage(float DamageAmount);

	UFUNCTION(BlueprintCallable, Category="Operator")
	void RestoreHealth(float HealAmount);

	UFUNCTION(BlueprintCallable, Category="Operator")
	bool ConsumeStamina(float StaminaAmount);

	UFUNCTION(BlueprintCallable, Category="Operator")
	void AddSuppression(float SuppressionAmount);

	UFUNCTION(BlueprintPure, Category="Operator")
	float GetHealth() const { return Health; }

	UFUNCTION(BlueprintPure, Category="Operator")
	float GetMaxHealth() const { return MaxHealth; }

	UFUNCTION(BlueprintPure, Category="Operator")
	float GetStamina() const { return Stamina; }

	UFUNCTION(BlueprintPure, Category="Operator")
	float GetMaxStamina() const { return MaxStamina; }

	UFUNCTION(BlueprintPure, Category="Operator")
	float GetSuppression() const { return Suppression; }

	UFUNCTION(BlueprintPure, Category="Operator")
	bool IsAlive() const { return Health > 0.0f; }

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditDefaultsOnly, Category="Operator|Health", meta=(ClampMin="1.0"))
	float MaxHealth = 100.0f;

	UPROPERTY(VisibleInstanceOnly, Category="Operator|Health")
	float Health = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category="Operator|Stamina", meta=(ClampMin="1.0"))
	float MaxStamina = 100.0f;

	UPROPERTY(VisibleInstanceOnly, Category="Operator|Stamina")
	float Stamina = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category="Operator|Stamina", meta=(ClampMin="0.0"))
	float StaminaRecoveryPerSecond = 16.0f;

	UPROPERTY(VisibleInstanceOnly, Category="Operator|Suppression", meta=(ClampMin="0.0", ClampMax="1.0"))
	float Suppression = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category="Operator|Suppression", meta=(ClampMin="0.0"))
	float SuppressionRecoveryPerSecond = 0.2f;
};
