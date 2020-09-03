
#include "TXAsset.h"

// properties

// constructor
TXAsset::TXAsset (int assetTypeArg, string fileNameArg, int assetIDArg, int assetBankNoArg)
{
    setup (assetTypeArg, fileNameArg, assetIDArg, assetBankNoArg);
}

// methods
void TXAsset::setup (int assetTypeArg, string fileNameArg, int assetIDArg, int assetBankNoArg)
{
    // create input paramaters
    parameters.clear();
    
 	parameters.add(assetType.set("assetType", assetTypeArg));
 	parameters.add(fileName.set("fileName", fileNameArg));
 	parameters.add(assetID.set("assetID", assetIDArg));
    parameters.add(assetBankNo.set("assetBankNo", assetBankNoArg));
}

int TXAsset::getAssetType() {
    return assetType;
}

string TXAsset::getAssetTypeString() {
    switch (assetType) {
        case TXASSETTYPE_IMAGE:
            return "Image";
            break;
        case TXASSETTYPE_MOVIE:
            return "Movie";
            break;
        case TXASSETTYPE_SVG:
            return "svg";
            break;
        case TXASSETTYPE_CUBE:
            return "cube";
            break;
        case TXASSETTYPE_3DMODEL:
            return "3DModel";
            break;
        case TXASSETTYPE_FONT:
            return "Font";
            break;
        default:
            return "Invalid Asset Type";
            break;
    }
}

void  TXAsset::setAssetType(int assetTypeArg) {
    assetType.set(assetTypeArg);
}

int TXAsset::getAssetID() {
    return assetID;
}

void  TXAsset::setAssetID(int assetIDArg) {
    assetID.set(assetIDArg);
}

string TXAsset::getFileName() {
    return fileName;
}

void  TXAsset::setFileName(string fileNameArg) {
    fileName.set(fileNameArg);
}

bool  TXAsset::getFileExists() {
    return ofFile(ofToString(fileName)).exists();
}

int TXAsset::getAssetBankNo() {
    return assetBankNo;
}

void  TXAsset::setAssetBankNo(int assetBankNoArg) {
    assetBankNo.set(assetBankNoArg);
}

