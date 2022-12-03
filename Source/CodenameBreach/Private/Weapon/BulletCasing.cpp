// Copyright 2017-2022 Wabbit, LLC. All Rights Reserved.


#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Weapon/BulletCasing.h"

ABulletCasing::ABulletCasing()
{
	PrimaryActorTick.bCanEverTick = false;

	CasingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CasingMesh"));
	SetRootComponent(CasingMesh);
	CasingMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	CasingMesh->SetSimulatePhysics(true);
	CasingMesh->SetEnableGravity(true);
	CasingMesh->SetNotifyRigidBodyCollision(true);
	ShellEjectionImpulse = 30.f;
}

void ABulletCasing::BeginPlay()
{
	Super::BeginPlay();
	
	CasingMesh->OnComponentHit.AddDynamic(this, &ABulletCasing::OnHit);
	CasingMesh->AddImpulse(GetActorForwardVector() * ShellEjectionImpulse);

	SetLifeSpan(3.f);
}

void ABulletCasing::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (ShellSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ShellSound, GetActorLocation());
	}
	CasingMesh->SetNotifyRigidBodyCollision(false);
}



