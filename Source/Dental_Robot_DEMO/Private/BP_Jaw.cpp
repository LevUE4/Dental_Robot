// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_Jaw.h"

// Sets default values
ABP_Jaw::ABP_Jaw()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Http = &FHttpModule::Get();
}

// Called when the game starts or when spawned
void ABP_Jaw::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABP_Jaw::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void  ABP_Jaw::requestHttpJawData(FString url) {
	FHttpRequestRef request = Http->CreateRequest();
	request->OnProcessRequestComplete().BindUObject(this, &ABP_Jaw::receiveHttpJawData);

	request->SetURL(url);
	request->SetVerb("GET");

	request->ProcessRequest();
}

void ABP_Jaw::parceHttpJawData(TSharedPtr<FJsonObject> data) {

	TArray<TSharedPtr<FJsonValue>>  temp_data;
	
	Xaccel = data->GetNumberField("x_accel");
	Yaccel = data->GetNumberField("y_accel");
	Zaccel = data->GetNumberField("z_accel");

	FFTVolume = data->GetNumberField("mic_fft_vol");

	temp_data = data->GetArrayField("orientation");

	Orientation0 = temp_data[0]->AsNumber();
	Orientation1 = temp_data[1]->AsNumber();
	Orientation2 = temp_data[2]->AsNumber();


	temp_data = data->GetArrayField("zone_force");

	ZoneF0 = temp_data[0]->AsNumber();
	ZoneF1 = temp_data[1]->AsNumber();
	ZoneF2 = temp_data[2]->AsNumber();
	ZoneF3 = temp_data[3]->AsNumber();


	temp_data = data->GetArrayField("touch_sense");

	TouchS0 = temp_data[0]->AsNumber();
	TouchS1 = temp_data[1]->AsNumber();
	TouchS2 = temp_data[2]->AsNumber();
	TouchS3 = temp_data[3]->AsNumber();
	TouchS4 = temp_data[4]->AsNumber();
	TouchS5 = temp_data[5]->AsNumber();
	TouchS6 = temp_data[6]->AsNumber();
	TouchS7 = temp_data[7]->AsNumber();
	TouchS8 = temp_data[8]->AsNumber();
	TouchS9 = temp_data[9]->AsNumber();
	TouchS10 = temp_data[10]->AsNumber();
	TouchS11 = temp_data[11]->AsNumber();
	TouchS12 = temp_data[12]->AsNumber();
	TouchS13 = temp_data[13]->AsNumber();


	temp_data = data->GetArrayField("temp_sense");

	TempS0 = temp_data[0]->AsNumber();
	TempS1 = temp_data[1]->AsNumber();
	TempS2 = temp_data[2]->AsNumber();
	TempS3 = temp_data[3]->AsNumber();
	TempS4 = temp_data[4]->AsNumber();
	TempS5 = temp_data[5]->AsNumber();
	TempS6 = temp_data[6]->AsNumber();
	TempS7 = temp_data[7]->AsNumber();
	TempS8 = temp_data[8]->AsNumber();
	TempS9 = temp_data[9]->AsNumber();
	TempS10 = temp_data[10]->AsNumber();
	TempS11 = temp_data[11]->AsNumber();
	TempS12 = temp_data[12]->AsNumber();
	TempS13 = temp_data[13]->AsNumber();
}

void  ABP_Jaw::receiveHttpJawData(FHttpRequestPtr request, FHttpResponsePtr response, bool isSuccessful) {
	
	if (!isSuccessful) return;

	TSharedRef<TJsonReader<TCHAR>> jsonReader = TJsonReaderFactory<TCHAR>::Create(response->GetContentAsString());

	TSharedPtr<FJsonObject> data;

	FJsonSerializer::Deserialize(jsonReader, data);

	parceHttpJawData(data);

	PullingDataComplete();
}





