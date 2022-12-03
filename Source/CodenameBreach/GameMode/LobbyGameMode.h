// Copyright 2017-2022 Wabbit, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CODENAMEBREACH_API ALobbyGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:

	virtual void PostLogin(APlayerController* NewPlayer) override;
};
