#include "ofApp.h"

void ofApp::setup() {
    ofSetFrameRate(60);
    ofBackground(0, 0, 0);
    ofEnableDepthTest();

    // Setup sfera
    sphereRadius = 150;
    sphere.setRadius(sphereRadius);
    sphere.setPosition(ofGetWidth()/2, ofGetHeight()/2, 0);
    sphere.setResolution(50);

    for(int i = 0; i < 200; i++) {
        glitchPoints.push_back(ofVec3f(
            ofRandom(-sphereRadius, sphereRadius),
            ofRandom(-sphereRadius, sphereRadius),
            ofRandom(-sphereRadius, sphereRadius)
        ));
    }

    rotationX = 0;
    rotationY = 0;
    isGlitching = false;
    glitchTimer = 0;
}

void ofApp::update() {
    noiseTime += 0.01;
    rotationX += 0.5;
    rotationY += 0.3;


    glitchTimer += 0.016;
    if(glitchTimer > ofRandom(0.5, 2.0)) {
        isGlitching = !isGlitching;
        glitchTimer = 0;
    }

   
    for(auto & point : glitchPoints) {
        if(isGlitching) {
            point.x += ofSignedNoise(noiseTime + point.x) * 5;
            point.y += ofSignedNoise(noiseTime + point.y) * 5;
            point.z += ofSignedNoise(noiseTime + point.z) * 5;

            // Mantieni i punti entro i limiti della sfera
            if(point.length() > sphereRadius) {
                point.normalize() *= sphereRadius;
            }
        }
    }
}

void ofApp::drawWaveBackground() {
    /* int width = ofGetWidth();
    int height = ofGetHeight();
    float time = ofGetElapsedTimef();

    for (int y = 0; y < height; y += 4) {
        for (int x = 0; x < width; x += 4) {
            float wave1 = sin(x * 0.05 + time * 0.5) * 2;
            float wave2 = cos(y * 0.06 + time * 0.4) * 2;
            float wave3 = sin((x + y) * 0.015 + time * 0.7) * 2;
            float z = wave1 + wave2 + wave3;

            float brightness = ofMap(z, -6, 6, 150, 255);
            int gray = ofRandom(180, 255);

            ofSetColor(gray, gray, gray, brightness);
            ofDrawCircle(x, y, 1);
        }
    } */
}

void ofApp::drawGlitchSphere() {
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2, 0);
    ofRotateXDeg(rotationX);
    ofRotateYDeg(rotationY);

    // sfera 
    /* ofSetColor(100, 144, 226, 180);
    sphere.drawWireframe(); */

    // Disegna punti glitch
    ofSetColor(255, 255, 255, 200);
    for(auto & point : glitchPoints) {
        if(isGlitching) {
            // Effetto glitch
            float glitchOffset = ofRandom(-2, 2);
            ofSetColor(255, ofRandom(100, 255), ofRandom(100, 255), 200);
            ofDrawBox(point.x + glitchOffset, point.y + glitchOffset, point.z + glitchOffset, 3);
        } else {
            ofDrawSphere(point, 1);
        }
    }

    // glitch 
    if(isGlitching) {
        for(int i = 0; i < 10; i++) {
            ofSetColor(ofRandom(100, 255), ofRandom(100, 255), 255, 100);
            float startAngle = ofRandom(360);
            float endAngle = startAngle + ofRandom(-30, 30);
            ofVec3f start = ofVec3f(cos(startAngle), sin(startAngle), 0) * sphereRadius;
            ofVec3f end = ofVec3f(cos(endAngle), sin(endAngle), 0) * sphereRadius;
            ofDrawLine(start, end);
        }
    }

    ofPopMatrix();
}

void ofApp::draw() {
    drawWaveBackground();
    drawGlitchSphere();

    ofSetColor(255);
    string status = isGlitching ? "GLITCHING" : "NORMAL";
    ofDrawBitmapString("FPS: " + ofToString(ofGetFrameRate()) + "\nStatus: " + status, 10, 20);
}

void ofApp::exit() {
}

void ofApp::keyPressed(int key) {
    if(key == ' ') {
        isGlitching = !isGlitching;
    }
}

void ofApp::keyReleased(int key){}
void ofApp::mouseMoved(int x, int y){}
void ofApp::mouseDragged(int x, int y, int button){}
void ofApp::mousePressed(int x, int y, int button){}
void ofApp::mouseReleased(int x, int y, int button){}
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){}
void ofApp::mouseEntered(int x, int y){}
void ofApp::mouseExited(int x, int y){}
void ofApp::windowResized(int w, int h){}
void ofApp::gotMessage(ofMessage msg){}
void ofApp::dragEvent(ofDragInfo dragInfo){}