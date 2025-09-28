// Fill out your copyright notice in the Description page of Project Settings.


#include "Minki/Time/TimeManager.h"
#include "Engine/DirectionalLight.h"
#include "Components/LightComponent.h"
#include "Components/SkyLightComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/SkyLight.h"
#include "Engine/PostProcessVolume.h"
#include "Components/SkyAtmosphereComponent.h"

ATimeManager::ATimeManager()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ATimeManager::BeginPlay()
{
    Super::BeginPlay();
}

void ATimeManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!DirectionalLight || DayLengthInSeconds <= 0.f)
        return;

    // 하루 시간 업데이트 (0~1)
    TimeOfDay += DeltaTime / DayLengthInSeconds;
    TimeOfDay = FMath::Fmod(TimeOfDay, 1.f);

    // 태양 각도: 0 = 정오, 0.5 = 자정 (180도 회전)
    // 태양이 떠있는지(밝기) 계산 (sin 곡선)
    float SunAngle = TimeOfDay * 360.f - 90.f; // -90도 해서 0시 -> 태양 아래 시작
    float SunPitch = FMath::Clamp(SunAngle, -90.f, 270.f);

    // 태양 방향 회전 (Pitch 축만 조절)
    FRotator SunRotation(SunPitch, -45.f, 0.f); // -45도 Yaw 예시 (동쪽 방향 기준)
    DirectionalLight->SetActorRotation(SunRotation);

    // 태양 강도 (낮일 때만 세기)
    float SunStrength = FMath::Clamp(FMath::Sin(FMath::DegreesToRadians(SunPitch)), 0.f, 1.f);
    float NewIntensity = FMath::Lerp(0.f, MaxSunIntensity, SunStrength);
    DirectionalLight->GetLightComponent()->SetIntensity(NewIntensity);

    // 태양 색상 (낮과 해질녘 색상 보간)
    FLinearColor DayColor(1.f, 0.95f, 0.8f);
    FLinearColor SunsetColor(1.f, 0.5f, 0.3f);
    FLinearColor NightColor(0.05f, 0.1f, 0.2f);

    FLinearColor SunColor;
    if (SunStrength > 0.1f)
    {
        float T = FMath::Clamp((SunStrength - 0.1f) / 0.8f, 0.f, 1.f);
        SunColor = FLinearColor::LerpUsingHSV(SunsetColor, DayColor, T);
    }
    else
    {
        SunColor = NightColor;
    }
    DirectionalLight->GetLightComponent()->SetLightColor(SunColor);

    // SkyLight 강도 및 색상 조절
    if (SkyLight)
    {
        float NewSkyIntensity = FMath::Lerp(0.1f, MaxSkyIntensity, SunStrength);
        SkyLight->GetLightComponent()->SetIntensity(NewSkyIntensity);

        FLinearColor DaySkyColor(0.6f, 0.7f, 1.f);
        FLinearColor NightSkyColor(0.02f, 0.02f, 0.05f);
        FLinearColor SkyColor = FLinearColor::LerpUsingHSV(NightSkyColor, DaySkyColor, SunStrength);
        SkyLight->GetLightComponent()->SetLightColor(SkyColor);

        SkyLight->GetLightComponent()->RecaptureSky();
    }

    // SkyAtmosphere에 태양 방향 전달
    if (SkyAtmosphere)
    {
        USkyAtmosphereComponent* SkyAtmosphereComp = SkyAtmosphere->GetSkyAtmosphereComponent();
        if (SkyAtmosphereComp)
        {
            // 태양 방향은 태양 라이트의 -X 방향 (Forward Vector)
            FVector SunDirection = DirectionalLight->GetActorForwardVector();
            SkyAtmosphereComp->SetSunDiskOverrideDirection(SunDirection);
            SkyAtmosphereComp->SetSunDiskLuminanceScale(SunStrength);
            SkyAtmosphereComp->SetAtmosphereSunLight(DirectionalLight->GetLightComponent());
        }
    }

    // PostProcessVolume으로 화면 톤 조절 (선택사항)
    if (PostProcessVolume)
    {
        PostProcessVolume->bUnbound = true;

        // Auto Exposure 끄기
        PostProcessVolume->Settings.bOverride_AutoExposureMinBrightness = true;
        PostProcessVolume->Settings.AutoExposureMinBrightness = 1.0f;
        PostProcessVolume->Settings.bOverride_AutoExposureMaxBrightness = true;
        PostProcessVolume->Settings.AutoExposureMaxBrightness = 1.0f;

        // 색상 보정
        PostProcessVolume->Settings.bOverride_SceneColorTint = true;
        FLinearColor DayTint(1.f, 0.95f, 0.9f);
        FLinearColor NightTint(0.1f, 0.15f, 0.3f);
        FLinearColor CurrentTint = FLinearColor::LerpUsingHSV(NightTint, DayTint, SunStrength);
        PostProcessVolume->Settings.SceneColorTint = CurrentTint;

        // 컨트라스트 조절
        PostProcessVolume->Settings.bOverride_Contrast = true;
        PostProcessVolume->Settings.Contrast = FMath::Lerp(0.8f, 1.1f, SunStrength);

        // 밝기 조절
        PostProcessVolume->Settings.bOverride_Brightness = true;
        PostProcessVolume->Settings.Brightness = FMath::Lerp(0.7f, 1.0f, SunStrength);
    }
}
