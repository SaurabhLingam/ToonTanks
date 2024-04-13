// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "BasePawn.h"


void ATower::BeginPlay(){
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::Tick(float DeltaTime){
    Super::Tick(DeltaTime);

    if(IsInFireRange()){
        RotateTurret(Tank->GetActorLocation());
    }

    
}

void ATower::HandleDestruction(){
    Super::HandleDestruction();

    Destroy();
}

void ATower::CheckFireCondition(){
    
    if(IsInFireRange()){
        Fire();
    }
    
}

bool ATower::IsInFireRange(){
    
    if(Tank){
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
        if(Distance<=FireRange){
            return true;
        }
    }

    return false;
}