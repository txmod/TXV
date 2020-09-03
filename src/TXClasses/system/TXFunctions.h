/*
 *  Created by paul on 09/09/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once


#include "ofMain.h"


class TXFunctions 
{
public:
		    
    static float cosineInterpolate( float point1, float point2, float inbetween)
    {
        float holdVal;
        
        holdVal = (1 - cos(inbetween * PI)) * 0.5;
        return (point1 * (1 - holdVal) + point2 * holdVal);
    }
    
    static int quantise(float floatArg) {
        int outValue;
        if (floatArg > 0) {
            outValue = (int) (floatArg + 0.5);
        } else {
            outValue = (int) (floatArg - 0.5);
        };
        return outValue;
    }
    
    static float getInterp(float val1, float val2, float proportion) {
        if ((val1 == val2) || (proportion == 0.0)) {
            return val1;
        } else if (proportion == 1.0) {
            return val2;
        } else {
            return ofLerp(val1, val2, proportion);
        };
    };
   
    static float getInterpCurves(TXParameterFloat256 & curve1, TXParameterFloat256 & curve2, float & curveLookup, float & curveMorph) {
        if (curveMorph <= 0.0) {
            return curve1.interpolatedLookup(curveLookup);
        } else if (curveMorph >= 1.0) {
            return curve2.interpolatedLookup(curveLookup);
        } else {
            return ofLerp(curve1.interpolatedLookup(curveLookup), curve2.interpolatedLookup(curveLookup), curveMorph);
        };
    };
    
    static float getInterpPhaseCurves(TXParameterFloat256 & curve1, TXParameterFloat256 & curve2, float & curveLookup, float & phase, float & curveMorph) {
        if (curveMorph <= 0.0) {
            return curve1.interpolatedLookupWithPhase(curveLookup, phase);
        } else if (curveMorph >= 1.0) {
            return curve2.interpolatedLookupWithPhase(curveLookup, phase);
        } else {
            return ofLerp(curve1.interpolatedLookupWithPhase(curveLookup, phase),
                          curve2.interpolatedLookupWithPhase(curveLookup, phase),
                          curveMorph);
        };
    };
    
    static ofColor txGetColor(float hue,
                            float saturation,
                            float brightness,
                            float alpha,
                            float hueRotation,
                            bool asRGB) {
        ofColor holdColor;
        if (asRGB) {
            holdColor.set(hue * 255, saturation * 255,  brightness * 255,  alpha * 255);
        } else {
            holdColor = ofColor::fromHsb(fmod(hue + hueRotation, 1.0f) * 255, saturation * 255,  brightness * 255,  alpha * 255);
        };
        return holdColor;
    }
    
    static void rotate(float rotX, float rotY, float rotZ) {
        ofVec3f Znormal(0, 0, 1);
        ofVec3f Xnormal(1, 0, 0);
        //ofVec3f Ynormal(1, 0, 1);
        ofVec3f Ynormal(0, 1, 0);
        
        //ofQuaternion constructor: angle, ofVec3f axis
        ofQuaternion qr (rotZ, Znormal); // quat roll.
        ofQuaternion qp (rotX, Xnormal); // quat pitch.
        ofQuaternion qh (rotY, Ynormal); // quat heading or yaw.
        ofQuaternion qt; // quat total.
        // The order IS IMPORTANT. Apply roll first, then pitch, then heading.
        qt = qr * qp * qh;
        
        ofVec3f qaxis;
        float qangle;
        qt.getRotate(qangle, qaxis);
        ofRotate(qangle, qaxis.x, qaxis.y, qaxis.z);
    }

    static ofVec3f txVectorRotate(ofVec3f inVector, float rotX, float rotY, float rotZ) {
        ofVec3f Znormal(0, 0, 1);
        ofVec3f Xnormal(1, 0, 0);
        //ofVec3f Ynormal(1, 0, 1);
        ofVec3f Ynormal(0, 1, 0);
        
        //ofQuaternion constructor: angle, ofVec3f axis
        ofQuaternion qr (rotZ, Znormal); // quat roll.
        ofQuaternion qp (rotX, Xnormal); // quat pitch.
        ofQuaternion qh (rotY, Ynormal); // quat heading or yaw.
        ofQuaternion qt; // quat total.
        // The order IS IMPORTANT. Apply roll first, then pitch, then heading.
        qt = qr * qp * qh;
        
        ofVec3f qaxis;
        float qangle;
        qt.getRotate(qangle, qaxis);
        ofVec3f outVector = inVector.rotate(qangle, qaxis);
        return outVector;
    }
    
    static ofQuaternion txGetRotateQuat(float rotX, float rotY, float rotZ) {
        ofVec3f Znormal(0, 0, 1);
        ofVec3f Xnormal(1, 0, 0);
        //ofVec3f Ynormal(1, 0, 1);
        ofVec3f Ynormal(0, 1, 0);
        //ofQuaternion constructor: angle, ofVec3f axis
        ofQuaternion qr (rotZ, Znormal); // quat roll.
        ofQuaternion qp (rotX, Xnormal); // quat pitch.
        ofQuaternion qh (rotY, Ynormal); // quat heading or yaw.
        ofQuaternion qt; // quat total.
        // The order IS IMPORTANT. Apply roll first, then pitch, then heading.
        qt = qr * qp * qh;
        return qt;
    }

    static ofMesh getIndiciedMeshFromNonIndiciedMesh( ofMesh & mesh, bool copyTexCoords = true, bool copyNormals = true ){
        
        ofMesh newMesh;
        vector < ofPoint > uniqueVertices;
        for (int i = 0; i < mesh.getVertices().size(); i++){
            
            int id = -1;
            for (int j = 0; j < uniqueVertices.size(); j++){
                if ( (uniqueVertices[j] - mesh.getVertices()[i]).length() < 0.1f){
                    id = j;
                }
            }
            
            if (id == -1){
                uniqueVertices.push_back(mesh.getVertices()[i]);
                id = uniqueVertices.size() - 1;
                newMesh.addVertex(mesh.getVertices()[i]);
                if (copyTexCoords && mesh.hasTexCoords()) {
                    newMesh.addTexCoord(mesh.getTexCoords()[i]);
                };
                if (copyNormals && mesh.hasNormals()) {
                    newMesh.addNormal(mesh.getNormals()[i]);
                };
            }
            
            newMesh.addIndex(id);
        }
        return newMesh;
    }

    
    /* NOT USED YET - UNTESTED
    static ofVec3f txPointMorphLinear2In(ofVec3f inputA, ofVec3f inputB, float proportion)
    {
        ofVec3f outPoint;
        outPoint = inputA.getInterpolated(inputB, proportion);
        return outPoint;
    }
    
    static ofVec3f txPointMorphLinear3In(ofVec3f inputA, ofVec3f inputB, ofVec3f inputC, float proportion)
    {
        ofVec3f outPoint;
        float holdProp;
        if (proportion <= 0.5) {
            holdProp = proportion * 2;
            outPoint = inputA.getInterpolated(inputB, holdProp);
        } else {
            holdProp = (proportion - 0.5) * 2;
            outPoint = inputB.getInterpolated(inputC, holdProp);
        }
        return outPoint;
    }
    
    static ofVec3f txPointMorphLinear4In(ofVec3f inputA, ofVec3f inputB, ofVec3f inputC, ofVec3f inputD, float proportion)
    {
        ofVec3f outPoint;
        float holdProp;
        if (proportion <= 0.33333333) {
            holdProp = proportion * 3;
            outPoint = inputA.getInterpolated(inputB, holdProp);
        } else if (proportion <= 0.6666666) {
            holdProp = (proportion - 0.33333333) * 3;
            outPoint = inputB.getInterpolated(inputC, holdProp);
        } else {
            holdProp = (proportion - 0.6666666) * 3;
            outPoint = inputC.getInterpolated(inputD, holdProp);
        }
        return outPoint;
    }
    
    static ofVec3f txPointMorphLinear5In(ofVec3f inputA, ofVec3f inputB, ofVec3f inputC, ofVec3f inputD, ofVec3f inputE, float proportion)
    {
        ofVec3f outPoint;
        float holdProp;
        if (proportion <= 0.25) {
            holdProp = proportion * 4;
            outPoint = inputA.getInterpolated(inputB, holdProp);
        } else if (proportion <= 0.5) {
            holdProp = (proportion - 0.25) * 4;
            outPoint = inputB.getInterpolated(inputC, holdProp);
        } else if (proportion <= 0.75) {
            holdProp = (proportion - 0.5) * 4;
            outPoint = inputC.getInterpolated(inputD, holdProp);
        } else {
            holdProp = (proportion - 0.75) * 4;
            outPoint = inputD.getInterpolated(inputE, holdProp);
        }
        return outPoint;
    }
    
    // NOT FINISHED ====
     
    static ofVec3f txPointMorph2D4In(ofVec3f inputA, ofVec3f inputB, ofVec3f inputC, ofVec3f inputD, float proportionX, float proportionY)
    {
        ofVec3f outPoint;
        outPoint = inputA.getInterpolated(inputB, proportion);
        return outPoint;
    }
    
    static ofVec3f txPointMorph2D5In(ofVec3f inputA, ofVec3f inputB, ofVec3f inputC, ofVec3f inputD, ofVec3f inputE, float proportionX, float proportionY)
    {
        // NOT FINISHED
        ofVec3f outPoint;
        outPoint = inputA.getInterpolated(inputB, proportion);
        return outPoint;
    }
*/
   
};
