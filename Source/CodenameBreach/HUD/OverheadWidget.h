// Copyright 2017-2022 Wabbit, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OverheadWidget.generated.h"

class  UTextBlock;

/**
 * 
 */
UCLASS()
class CODENAMEBREACH_API UOverheadWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DisplayText;

	void SetDisplayText(FString TextToDisplay);

	UFUNCTION(BlueprintCallable)
	void ShowPlayerNetRole(APawn* InPawn);

protected:

	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;
};
