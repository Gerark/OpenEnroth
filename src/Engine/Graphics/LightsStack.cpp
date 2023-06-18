#include "Library/Logger/Logger.h"

#include "Engine/Graphics/LightsStack.h"

//----- (00467D88) --------------------------------------------------------
bool LightsStack_MobileLight_::AddLight(const Vec3f &pos, int16_t uSectorID, int uRadius, Color color, char uLightType) {
    if (uNumLightsActive >= 400) {
        log->warning("Too many mobile lights!");
        return false;
    }

    pLights[uNumLightsActive].vPosition = pos;
    pLights[uNumLightsActive].uRadius = uRadius;
    pLights[uNumLightsActive].field_C = (((uRadius < 0) - 1) & 0x3E) - 31;
    pLights[uNumLightsActive].uSectorID = uSectorID;
    pLights[uNumLightsActive].field_10 = uRadius * uRadius >> 5;
    pLights[uNumLightsActive].uLightColor = color;
    pLights[uNumLightsActive++].uLightType = uLightType;

    return true;
}

bool LightsStack_StationaryLight_::AddLight(const Vec3f &pos, int16_t a5, Color color, char uLightType) {
    if (uNumLightsActive >= 400) {
        log->warning("Too many stationary lights!");
        return false;
    }

    StationaryLight *pLight = &pLights[uNumLightsActive++];
    pLight->vPosition = pos;
    pLight->uRadius = a5;
    pLight->uLightColor = color;
    pLight->uLightType = uLightType;
    return true;
}
