// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GhostsHUDWidget.h"
#include "GhostsPlayerController.generated.h"

class UInputMappingContext;
class UUserWidget;

/**
 *  Simple first person Player Controller
 *  Manages the input mapping context.
 *  Overrides the Player Camera Manager class.
 */
UCLASS(abstract, config="Game")
class GHOSTS_API AGhostsPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	/** Constructor */
	AGhostsPlayerController();

	UFUNCTION(BlueprintPure, Category="HUD")
	UGhostsHUDWidget* GetHUDWidget() const { return HUDWidget; }

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void UpdateHealthHUD(float CurrentHealth, float MaxHealth);

protected:

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category="Input|Input Mappings")
	TArray<UInputMappingContext*> DefaultMappingContexts;

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category="Input|Input Mappings")
	TArray<UInputMappingContext*> MobileExcludedMappingContexts;

	/** Mobile controls widget to spawn */
	UPROPERTY(EditAnywhere, Category="Input|Touch Controls")
	TSubclassOf<UUserWidget> MobileControlsWidgetClass;

	/** Pointer to the mobile controls widget */
	UPROPERTY()
	TObjectPtr<UUserWidget> MobileControlsWidget;

	UPROPERTY(EditAnywhere, Category="HUD")
	TSubclassOf<UGhostsHUDWidget> HUDWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "HUD")
	UGhostsHUDWidget* HUDWidget;

	/** If true, the player will use UMG touch controls even if not playing on mobile platforms */
	UPROPERTY(EditAnywhere, Config, Category = "Input|Touch Controls")
	bool bForceTouchControls = false;

	/** Gameplay initialization */
	virtual void BeginPlay() override;

	/** Input mapping context setup */
	virtual void SetupInputComponent() override;

	/** Returns true if the player should use UMG touch controls */
	bool ShouldUseTouchControls() const;
};
