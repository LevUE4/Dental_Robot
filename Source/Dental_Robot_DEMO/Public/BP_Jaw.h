// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BP_Jaw.generated.h"


UCLASS()
class DENTAL_ROBOT_DEMO_API ABP_Jaw : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABP_Jaw();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sensors")
	float Temperatura;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sensors")
	float Sound;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sensors")
	float Pressure;

};
