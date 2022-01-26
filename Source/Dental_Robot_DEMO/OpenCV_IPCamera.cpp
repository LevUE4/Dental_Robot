// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenCV_IPCamera.h"

// Sets default values
AOpenCV_IPCamera::AOpenCV_IPCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RefreshRate = 30.0f;

    VideoSize.X = 640;
    VideoSize.Y = 480;

    cvMat = cv::Mat();
    cvCapture = cv::VideoCapture();
}

// Called when the game starts or when spawned
void AOpenCV_IPCamera::BeginPlay()
{
	Super::BeginPlay();
	cvCapture.open("http://" + std::string(TCHAR_TO_UTF8(*CameraAddress)) + "/get?id=0.69");
	cameraUpdateAddress = "http://" + std::string(TCHAR_TO_UTF8(*CameraAddress)) + "/out.jpg?q=75&id=0.69";

    cvSize = cv::Size(VideoSize.X, VideoSize.Y);

    Data.Init(FColor(0, 0, 0, 255), VideoSize.X * VideoSize.Y);

    OpenCV_Texture2D = UTexture2D::CreateTransient(VideoSize.X, VideoSize.Y);
    OpenCV_Texture2D->SRGB = 0;

    cvCapture.open(0); // WEB CAMERA // 
}

// Called every frame
void AOpenCV_IPCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RefreshTimer += DeltaTime;
	if (RefreshTimer >= 1.0f / RefreshRate) {
		RefreshTimer -= 1.0f / RefreshRate;
		ReadFrame();
		OnNextVideoFrame();
	}

}

bool  AOpenCV_IPCamera::ReadFrame() {

    //cvCapture.open(cameraUpdateAddress); // IP CAMERA //

	cvCapture.read(cvMat);
    
	if (!cvMat.empty())
		cv::imshow(cameraUpdateAddress, cvMat);

    cv::cvtColor(cvMat, cvMat, cv::COLOR_BGR2RGBA);

	FTexture2DMipMap& mip = OpenCV_Texture2D->PlatformData->Mips[0];
	void* data = mip.BulkData.Lock(LOCK_READ_WRITE);
	auto stride = (int32)(sizeof(uint8)*4); // for r, g, b, a
	FMemory::Memcpy(data, cvMat.data, cvMat.size().width * cvMat.size().height*stride);
	mip.BulkData.Unlock();
	OpenCV_Texture2D->UpdateResource();
    
	return !cvMat.empty();
}

