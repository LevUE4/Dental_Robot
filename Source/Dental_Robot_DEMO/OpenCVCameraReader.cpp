// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenCVCameraReader.h"

// Sets default values
AOpenCVCameraReader::AOpenCVCameraReader(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ensure the root component exists
	if (!RootComponent)
		RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, false);

	// Create and attach sub components
	RScreen = CreateDefaultSubobject<UStaticMeshComponent>("Right screen");
	RScreen->AttachToComponent(RootComponent, rules);
	LScreen = CreateDefaultSubobject<UStaticMeshComponent>("Left screen");
	LScreen->AttachToComponent(RootComponent, rules);

	// setup property defaults
	ColorMode = ETextureRenderTargetFormat::RTF_RGBA8;

	// Initialize OpenCV and webcam properties
	RCameraID = 0;
	RVideoTrackID = 0;

	LCameraID = 1;
	LVideoTrackID = 0;


	VideoSize = FVector2D(640, 480);
	RefreshRate = 30.0f;
}

// Called when the game starts or when spawned
void AOpenCVCameraReader::BeginPlay()
{
	Super::BeginPlay();

	// Prepare the color data array
	RColorData.AddDefaulted(VideoSize.X * VideoSize.Y);
	LColorData.AddDefaulted(VideoSize.X * VideoSize.Y);

	// setup openCV
	cvSize = cv::Size(VideoSize.X, VideoSize.Y);
	int cvColorMode = GetColorMode_CV();
	rCVMat = cv::Mat(cvSize, cvColorMode, RColorData.GetData());
	lCVMat = cv::Mat(cvSize, cvColorMode, LColorData.GetData());

	// create dynamic texture
	ROpenCV_Texture2D = UTexture2D::CreateTransient(VideoSize.X, VideoSize.Y, PF_B8G8R8A8);
	LOpenCV_Texture2D = UTexture2D::CreateTransient(VideoSize.X, VideoSize.Y, PF_B8G8R8A8);

#if WITH_EDITORONLY_DATA
	ROpenCV_Texture2D->MipGenSettings = TMGS_NoMipmaps;
	LOpenCV_Texture2D->MipGenSettings = TMGS_NoMipmaps;
#endif
	ROpenCV_Texture2D->SRGB = RCameraRenderTarget->SRGB;
	LOpenCV_Texture2D->SRGB = LCameraRenderTarget->SRGB;
}

// Called every frame
void AOpenCVCameraReader::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RefreshTimer += DeltaTime;
	if (RefreshTimer >= 1.0f / RefreshRate) {
		RefreshTimer -= 1.0f / RefreshRate;
		ReadFrame();
		ProcessFrame();
		UpdateTextureFromFrame();
		OnNextVideoFrame();
	}
}

int AOpenCVCameraReader::GetColorMode_CV() {
	int cvColorMode = CV_8UC4;
	switch (ColorMode)
	{
	case ETextureRenderTargetFormat::RTF_RGBA8:
		cvColorMode = CV_8UC4;
		break;
	case ETextureRenderTargetFormat::RTF_RGBA16f:
		UE_LOG(LogTemp, Warning, TEXT("16 bit not yet supported, Only 8 bit colour implemented currently will always return CV_8UC4"));
		cvColorMode = CV_16FC4;
		break;
	case ETextureRenderTargetFormat::RTF_RGBA32f:
		UE_LOG(LogTemp, Warning, TEXT("32 bit not yet supported, Only 8 bit colour implemented currently will always return CV_8UC4"));
		cvColorMode = CV_32FC4;
		break;
	default:
		// TODO Error unrecognized color format!
		cvColorMode = CV_8UC4;
		break;
	}
	return cvColorMode;
}

bool AOpenCVCameraReader::ReadFrame() {
	if (!ROpenCV_Texture2D || !RCameraRenderTarget ||
		!LOpenCV_Texture2D || !LCameraRenderTarget) return false;

	int cvColorMode = GetColorMode_CV();

	FRenderTarget* rCamRenderTarget = RCameraRenderTarget->GameThread_GetRenderTargetResource();
	FRenderTarget* lCamRenderTarget = LCameraRenderTarget->GameThread_GetRenderTargetResource();

	rCamRenderTarget->ReadPixels(RColorData);
	lCamRenderTarget->ReadPixels(LColorData);

	rCVMat = cv::Mat(cvSize, cvColorMode, RColorData.GetData());
	lCVMat = cv::Mat(cvSize, cvColorMode, LColorData.GetData());

	return rCVMat.empty() && lCVMat.empty();
}


void AOpenCVCameraReader::ProcessFrame() {
	
	//cv::Mat MATb;
	//cv::Ptr<cv::Feature2D> f2d = cv::SIFT::create();
	//std::vector<cv::KeyPoint> *keypoints_1 = new std::vector<cv::KeyPoint>();
	//auto ptr = cv::Ptr<std::vector<cv::KeyPoint>>(keypoints_1);

	//f2d->detect(rCVMat, *keypoints_1);
	////f2d->detect(frame2, keypoints_2);

	//cv::Mat output;

	//cv::drawKeypoints(rCVMat, *keypoints_1, output);
	//cv::imshow("surf_result.jpg", output);

	//cv::InputArray

	//rCVMat
}


void AOpenCVCameraReader::UpdateTextureFromFrame() {

	void* RTextureData = ROpenCV_Texture2D->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
	void* LTextureData = LOpenCV_Texture2D->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);

	const int32 RTextureDataSize = RColorData.Num() * 4;
	const int32 LTextureDataSize = LColorData.Num() * 4;

	FMemory::Memcpy(RTextureData, RColorData.GetData(), RTextureDataSize);
	FMemory::Memcpy(LTextureData, LColorData.GetData(), LTextureDataSize);

	ROpenCV_Texture2D->PlatformData->Mips[0].BulkData.Unlock();
	LOpenCV_Texture2D->PlatformData->Mips[0].BulkData.Unlock();

	ROpenCV_Texture2D->UpdateResource();
	LOpenCV_Texture2D->UpdateResource();

	/*
	//Wrapped in a render command for performance
	ENQUEUE_RENDER_COMMAND(WriteOpenCVTexture)(
		[RTarget = RenderTarget, RTexture = OpenCV_Texture2D, ColorD = ColorData](FRHICommandList& RHICmdList)
		{

		});
	*/
}


