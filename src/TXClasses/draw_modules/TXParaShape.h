#pragma once

#include "ofMain.h"
#include "TXParaShapes.h"

    // NB change totalShapes if new shapes added
//  "Diamond", "Torus", "Ellipsoid", "Paraboloid", "HyperbolicParaboloid", "Hyperboloid1", "Hyperboloid2", "RightConoid", "Helicoid", "Periwinkle", "Topshell", "ConeShell", "Periwinkle2", "ToothedTopshell", "TurretShell", "ShellX", "SpindleShell", "Topshell2", "CrossCap", "Klein", "Klein2", "Cosinus", "Moebius", "Reiman", "Henneberg", "Enneper", "Enneper2", "Helix", "Hexaedron", "Catalan", "Toupie", "Toupie2", "Trumpet", "Catenoid", "Crescent", "Crescent2", "HyperbolicHelicoid", "Horn", "Fresnel", "Steiner", "MaedersOwl", "TrippleFin", "EightSurface", "EightSurface2", "Roman", "Dini", "Apple", "Drop", "Kidney", "LimpetTorus", "Lemniscape", "Folium", "Seed", "PinchedSphere", "PinchedPillow", "TwistedSphere", "TwistedTorus", "Hurricane", "Star5",

class TXParaShape {

public:
    void setup(int paraShapeType = 0, float resUArg = 24, float resVArg = 24);
    void update();
    void draw();
    void setResolution(int resArg);
    
    ofPtr<TXParametricSurfaceBase> getShape();
    
    ofPtr<TXParametricSurfaceBase> newParaShape(int & argParaShapeType);
    
    static const int totalShapes = 59;
    
private:
    int paraShapeType = 0;
    ofPtr<TXParametricSurfaceBase> paraShape;

 };

