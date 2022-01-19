// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "MediaTexture.h"
#include "Runtime/Engine/Classes/Engine/Texture2D.h"
#include "Runtime/Engine/Classes/Engine/TextureRenderTarget2D.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OpenCVCameraReader.generated.h"

UCLASS()
class DENTAL_ROBOT_DEMO_API AOpenCVCameraReader : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOpenCVCameraReader(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = OpenCV)
		UStaticMeshComponent* Screen_Raw;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = OpenCV)
		UStaticMeshComponent* Screen_Post;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
		TEnumAsByte<ETextureRenderTargetFormat> ColorMode;

	// The device ID opened by the Video Stream
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Camera, meta = (ClampMin = 0, UIMin = 0))
		int32 CameraID;
	// The device ID opened by the Video Stream
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Camera, meta = (ClampMin = 0, UIMin = 0))
		int32 VideoTrackID;


	// The rate at which the color data array and video texture is updated (in frames per second)
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = OpenCV, meta = (ClampMin = 0, UIMin = 0))
		float RefreshRate;
	// The refresh timer
	UPROPERTY(BlueprintReadWrite, Category = OpenCV)
		float RefreshTimer;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = OpenCV)
		float Brightness;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = OpenCV)
		float Multiply;

	// The videos width and height (width, height)
	UPROPERTY(BlueprintReadWrite, Category = Input)
		FVector2D VideoSize;


	// Camera Media Player
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Input)
		UMediaPlayer* MediaPlayer;

	// Camera Media Texture
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Input)
		UMediaTexture* MediaTexture;


	// 8 bit Render Target (Pre Edit)
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Materials)
		UTextureRenderTarget2D* RenderTarget;

	// Draws OpenCV_Texture2D (Post Edit)
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Materials)
		UMaterialInstanceDynamic* Material_Post;
	// Draws an assigned Render Target (Pre Edit)
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Materials)
		UMaterialInstanceDynamic* Material_RenderTarget;

	// OpenCV Texture (Post Edit)
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = OpenCV)
		UTexture2D* OpenCV_Texture2D;
	// Color Data
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Data)
		TArray<FColor> ColorData;


	UFUNCTION(BlueprintImplementableEvent, Category = OpenCV)
		void OnNextVideoFrame();
	// reads the current video frame
	UFUNCTION(BlueprintCallable, Category = Data)
		bool ReadFrame();

	//OpenCV
	cv::Size cvSize;
	cv::Mat cvMat;

	int GetColorMode_CV();

	UFUNCTION(BlueprintCallable, Category = Status)
		void NextCamera();
	UFUNCTION(BlueprintCallable, Category = Status)
		void NextVideoTrack();
	UFUNCTION(BlueprintImplementableEvent, Category = Camera)
		void ValidateVideoTrackID();
	UFUNCTION(BlueprintImplementableEvent, Category = Camera)
		void ValidateCameraID();

};
