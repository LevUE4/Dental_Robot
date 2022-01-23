// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "MediaTexture.h"
#include "Runtime/Engine/Classes/Engine/Texture2D.h"
#include "Components/StaticMeshComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OpenCV_IPCamera.generated.h"

UCLASS()
class DENTAL_ROBOT_DEMO_API AOpenCV_IPCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOpenCV_IPCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Connection)
		FString CameraAddress;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = OpenCV)
		float RefreshRate;
	// The refresh timer
	UPROPERTY(BlueprintReadWrite, Category = OpenCV)
		float RefreshTimer;


	UFUNCTION(BlueprintCallable, Category = Data)
		bool ReadFrame();
	UFUNCTION(BlueprintImplementableEvent, Category = OpenCV)
		void OnNextVideoFrame();

	// OpenCV Texture (Post Edit)
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = OpenCV)
		UTexture2D* OpenCV_Texture2D;

	cv::Size cvSize;
	cv::Mat cvMat;
	cv::VideoCapture cvCapture;

	// The videos width and height (width, height)
	UPROPERTY(BlueprintReadWrite, Category = Webcam)
		FVector2D VideoSize;
	
	UPROPERTY(BlueprintReadOnly, Category = Webcam)
		TArray<FColor> Data;

private:
	cv::String cameraUpdateAddress;
};
