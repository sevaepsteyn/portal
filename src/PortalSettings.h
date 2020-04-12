/* vim: set tabstop=4 shiftwidth=4 expandtab: */
#pragma once

class PortalSettings {

    public:
        PortalSettings() {
            translateX = 0;
            translateY = 0;

            sizeX = ofGetWindowWidth();
            sizeY = ofGetWindowHeight();

            totalX = sizeX;
            totalY = sizeY;

            shiftX = 0;
            borderX = 0;

            portalId = "n/a";
            mapId = "n/a";

            side = 0;
        }

        int translateX, translateY;
        int sizeX, sizeY;
        int totalX, totalY;
        int shiftX;
        int borderX;
        int side;

        string portalId;
        string mapId;
};
