// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Engine.h"

#include "Interfaces/IHttpRequest.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"

#include "BP_Jaw.generated.h"


UCLASS()
class DENTAL_ROBOT_DEMO_API ABP_Jaw : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABP_Jaw();

	FHttpModule* Http;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = Data)
		void requestHttpJawData(FString url);

	void receiveHttpJawData(FHttpRequestPtr request, FHttpResponsePtr response, bool isSuccessful);
	void parceHttpJawData(TSharedPtr<FJsonObject> data);


	UFUNCTION(BlueprintImplementableEvent, Category = Data)
		void PullingDataComplete();



	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Accel)
		float Xaccel;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Accel)
		float Yaccel;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Accel)
		float Zaccel;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Orientation)
		float Orientation0;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Orientation)
		float Orientation1;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Orientation)
		float Orientation2;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Microphone)
		float FFTVolume;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = ZoneForce)
		float ZoneF0;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = ZoneForce)
		float ZoneF1;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = ZoneForce)
		float ZoneF2;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = ZoneForce)
		float ZoneF3;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = TouchSense)
		float TouchS0;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = TouchSense)
		float TouchS1;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = TouchSense)
		float TouchS2;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = TouchSense)
		float TouchS3;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = TouchSense)
		float TouchS4;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = TouchSense)
		float TouchS5;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = TouchSense)
		float TouchS6;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = TouchSense)
		float TouchS7;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = TouchSense)
		float TouchS8;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = TouchSense)
		float TouchS9;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = TouchSense)
		float TouchS10;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = TouchSense)
		float TouchS11;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = TouchSense)
		float TouchS12;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = TouchSense)
		float TouchS13;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = TempSense)
		float TempS0;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = TempSense)
		float TempS1;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = TempSense)
		float TempS2;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = TempSense)
		float TempS3;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = TempSense)
		float TempS4;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = TempSense)
		float TempS5;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = TempSense)
		float TempS6;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = TempSense)
		float TempS7;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = TempSense)
		float TempS8;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = TempSense)
		float TempS9;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = TempSense)
		float TempS10;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = TempSense)
		float TempS11;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = TempSense)
		float TempS12;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = TempSense)
		float TempS13;








};
