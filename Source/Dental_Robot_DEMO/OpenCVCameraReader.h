// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/features2d.hpp"

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
		UStaticMeshComponent* RScreen;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = OpenCV)
		UStaticMeshComponent* LScreen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
		TEnumAsByte<ETextureRenderTargetFormat> ColorMode;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Camera, meta = (ClampMin = 0, UIMin = 0))
		int32 RCameraID;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Camera, meta = (ClampMin = 0, UIMin = 0))
		int32 RVideoTrackID;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Camera, meta = (ClampMin = 0, UIMin = 0))
		int32 LCameraID;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Camera, meta = (ClampMin = 0, UIMin = 0))
		int32 LVideoTrackID;


	// The rate at which the color data array and video texture is updated (in frames per second)
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = OpenCV, meta = (ClampMin = 0, UIMin = 0))
		float RefreshRate;
	// The refresh timer
	UPROPERTY(BlueprintReadWrite, Category = OpenCV)
		float RefreshTimer;


	// The videos width and height (width, height)
	UPROPERTY(BlueprintReadWrite, Category = Input)
		FVector2D VideoSize;


	// 8 bit Render Target (Pre Edit)
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Materials)
		UTextureRenderTarget2D* RCameraRenderTarget;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Materials)
		UTextureRenderTarget2D* LCameraRenderTarget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Input)
		UMediaPlayer* RMediaPlayer;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Input)
		UMediaPlayer* LMediaPlayer;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Input)
		UMediaTexture* RMediaTexture;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Input)
		UMediaTexture* LMediaTexture;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Materials)
		UMaterialInstanceDynamic* RCameraMaterial;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Materials)
		UMaterialInstanceDynamic* LCameraMaterial;

	// Right OpenCV Texture (Post Edit)
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = OpenCV)
		UTexture2D* ROpenCV_Texture2D;
	// Left OpenCV Texture (Post Edit)
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = OpenCV)
		UTexture2D* LOpenCV_Texture2D;


	UFUNCTION(BlueprintImplementableEvent, Category = OpenCV)
		void OnNextVideoFrame();
	// reads the current video frame
	
	bool ReadFrame();
	void ProcessFrame();
	void UpdateTextureFromFrame();

	TArray<FColor> RColorData;
	TArray<FColor> LColorData;

	//OpenCV
	cv::Size cvSize;
	cv::Mat rCVMat;
	cv::Mat lCVMat;

	int GetColorMode_CV();

};
