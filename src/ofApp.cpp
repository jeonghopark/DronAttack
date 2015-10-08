#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground( 0 );
    
//    mainOffSetXPos = (ofGetWidth() - (baseArch.fassadeCorner[0].x + baseArch.fassadeCorner[1].x)) * 0.5;
//    mainOffSetYPos = (ofGetHeight() - (baseArch.fassadeCorner[0].y + baseArch.fassadeCorner[3].y)) * 0.5;
//    baseArch.mainOffSetXPos = mainOffSetXPos;
//    baseArch.mainOffSetYPos = mainOffSetYPos;

    earthFbo.allocate(ofGetWidth(), ofGetHeight());

    
    ofxJSONElement _drondata;
    _drondata.open("dropAttack_08102015.json");
    
    ofxJSONElement _dronStrike = _drondata["strike"];
    
    float _radiusEarth = 700;

    dronData.resize(_dronStrike.size());
    for (int i=0; i<_dronStrike.size(); i++){
        
        float _lat = _dronStrike[i]["lat"].asFloat();
        float _lon = _dronStrike[i]["lon"].asFloat();
        
        float _d = _dronStrike[i]["deaths_max"].asFloat();
        
        ofVec3f _v;
        _v.x = _radiusEarth * cos(ofDegToRad(_lat)) * cos(ofDegToRad(_lon));
        _v.y = _radiusEarth * cos(ofDegToRad(_lat)) * sin(ofDegToRad(_lon));
        _v.z = _radiusEarth *sin(ofDegToRad(_lat));
        
        dronData[i].deathMax = _d;
        dronData[i].coord = _v;
        
    }

    

    
    ofxJSONElement _jsonData;
    _jsonData.open("ne_110m_coastline.geojson");
    
    ofxJSONElement _jsonDataChild = _jsonData["features"];
    for (int i=0; i<_jsonDataChild.size(); i++) {
        ofxJSONElement _jsonGeoData = _jsonDataChild[i]["geometry"]["coordinates"];
        
        ofPolyline _p;
        
        for (int j=0; j<_jsonGeoData.size(); j++) {
            
            float _lon = _jsonGeoData[j][0].asFloat();
            float _lat = _jsonGeoData[j][1].asFloat();
            
            ofVec3f _v;
            _v.x = _radiusEarth * cos(ofDegToRad(_lat)) * cos(ofDegToRad(_lon));
            _v.y = _radiusEarth * cos(ofDegToRad(_lat)) * sin(ofDegToRad(_lon));
            _v.z = _radiusEarth *sin(ofDegToRad(_lat));
            
            
            _p.addVertex( _v );
            
        }
        
        oceanLineCoord.push_back( _p );
        
    }



}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    
    easyCam.begin();
    
    ofPushStyle();
    ofSetColor(255, 0, 0);
    for (int i=0; i<dronData.size(); i++) {
        ofVec3f _v = dronData[i].coord;
        
        float _ratio = ofMap(dronData[i].deathMax, 1, 30, 1.1, 1.2);
        
        ofDrawLine( _v, _v * _ratio );
    }
    
    ofPopStyle();
    

    ofPushStyle();
    ofSetColor(255);
    for (int i=0; i<oceanLineCoord.size(); i++) {
        oceanLineCoord[i].draw();
    }
    ofPopStyle();

    
    easyCam.end();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
