// Copyright 2017-2022 Wabbit, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletCasing.generated.h"

class USoundCue;

UCLASS()
class CODENAMEBREACH_API ABulletCasing : public AActor
{
	GENERATED_BODY()
	
public:	
	ABulletCasing();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


private:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CasingMesh;

	UPROPERTY(EditAnywhere)
	float ShellEjectionImpulse;

	UPROPERTY(EditAnywhere)
	USoundCue* ShellSound;

public:	
		
};
