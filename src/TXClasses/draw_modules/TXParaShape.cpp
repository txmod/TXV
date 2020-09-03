#include "TXParaShape.h"

//--------------------------------------------------------------
void TXParaShape::setup(int paraShapeTypeArg, float resUArg, float resVArg){
    paraShapeType = paraShapeTypeArg;
    paraShape = newParaShape(paraShapeTypeArg);
    paraShape->setup(resUArg, resVArg);
}

//--------------------------------------------------------------
ofPtr<TXParametricSurfaceBase> TXParaShape::newParaShape(int & argParaShapeType) {
    switch (argParaShapeType) {
        case 0:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_Diamond);
            break;
        case 1:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_Torus);
            break;
        case 2:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_Ellipsoid);
            break;
        case 3:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_Paraboloid);
            break;
        case 4:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_HyperbolicParaboloid);
            break;
        case 5:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_Hyperboloid1);
            break;
        case 6:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_Hyperboloid2);
            break;
        case 7:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_RightConoid);
            break;
        case 8:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_Helicoid);
            break;
        case 9:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_Periwinkle);
            break;
        case 10:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_Topshell);
            break;
        case 11:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_ConeShell);
            break;
        case 12:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_Periwinkle2);
            break;
        case 13:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_ToothedTopshell);
            break;
        case 14:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_TurretShell);
            break;
        case 15:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_ShellX);
            break;
        case 16:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_SpindleShell);
            break;
        case 17:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_Topshell2);
            break;
        case 18:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_CrossCap);
            break;
        case 19:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_Klien);
            break;
        case 20:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_Klein2);
            break;
        case 21:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_Cosinus);
            break;
        case 22:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_Moebius);
            break;
        case 23:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_Reiman);
            break;
        case 24:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_Henneberg);
            break;
        case 25:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_Enneper);
            break;
        case 26:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_Enneper2);
            break;
        case 27:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_Helix);
            break;
        case 28:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_Hexaedron);
            break;
        case 29:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_Catalan);
            break;
        case 30:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_Toupie);
            break;
        case 31:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_Toupie2);
            break;
        case 32:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_Trumpet);
            break;
        case 33:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_Catenoid);
            break;
        case 34:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_Crescent);
            break;
        case 35:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_Crescent2);
            break;
        case 36:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_HyperbolicHelicoid);
            break;
        case 37:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_Horn);
            break;
        case 38:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_Fresnel);
            break;
        case 39:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_Steiner);
            break;
        case 40:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_MaedersOwl);
            break;
        case 41:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_TrippleFin);
            break;
        case 42:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_EightSurface);
            break;
        case 43:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_EightSurface2);
            break;
        case 44:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_Roman);
            break;
        case 45:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_Dini);
            break;
        case 46:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_Apple);
            break;
        case 47:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_Drop);
            break;
        case 48:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_Kidney);
            break;
        case 49:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_LimpetTorus);
            break;
        case 50:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_Lemniscape);
            break;
        case 51:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_Folium);
            break;
        case 52:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_Seed);
            break;
        case 53:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_PinchedSphere);
            break;
        case 54:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_PinchedPillow);
            break;
        case 55:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_TwistedSphere);
            break;
        case 56:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_TwistedTorus);
            break;
        case 57:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_Hurricane);
            break;
        case 58:
            return ofPtr<TXParametricSurfaceBase>(new TXParaShape_Star5);
            break;
        default:
            break;
    };
}

//--------------------------------------------------------------
void TXParaShape::update(){
    paraShape->reload();
}

//--------------------------------------------------------------
void TXParaShape::draw(){
    ofBackground(0);
    ofEnableDepthTest();
    
    ofSetColor(255, 255, 255);

    paraShape->draw(false, true);

    ofDisableDepthTest();

}

void setResolution(int resArg) {
    
}

//--------------------------------------------------------------

ofPtr<TXParametricSurfaceBase> TXParaShape::getShape() {
    return paraShape;
};

