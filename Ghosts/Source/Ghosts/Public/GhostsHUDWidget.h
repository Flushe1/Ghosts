// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GhostsHUDWidget.generated.h"

UCLASS()
class GHOSTS_API UGhostsHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// Chamado pelo PlayerController para atualizar munição
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void UpdateAmmo(int32 RoundsInMagazine, int32 ReserveRounds);

protected:
	virtual void NativeConstruct() override;

	// Conecta automaticamente ao TextBlock de mesmo nome no Blueprint
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* AmmoText;
};
