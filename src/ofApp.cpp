#include "ofApp.h"
#include <string>

//--------------------------------------------------------------
void ofApp::setup(){
    sound.load("beat.wav"); //Loads a sound file (in bin/data/)
    sound.setLoop(true); // Makes the song loop indefinitely
    sound.setVolume(1); // Sets the song volume
    ofSetBackgroundColor(36, 32,56); // Sets the Background Color
}

//--------------------------------------------------------------
void ofApp::update(){
    /* The update method is called muliple times per second
    It's in charge of updating variables and the logic of our app */
    ofSoundUpdate(); // Updates all sound players
    if(!pause)
    {
    visualizer.updateAmplitudes(); // Updates Amplitudes for visualizer
    }
    tickCount++;
    playInput(record);


}

//--------------------------------------------------------------
void ofApp::draw(){
    /* The update method is called muliple times per second
    It's in charge of drawing all figures and text on screen */
    ofSetColor(256);
    if(!playing){
        ofDrawBitmapString("Press 'p' to play some music!", ofGetWidth()/2 - 50, ofGetHeight()/2);
    }
    vector<float> amplitudes = visualizer.getAmplitudes();
    switch(mode) {
        case '1': drawMode1(amplitudes); break;
        case '2': drawMode2(amplitudes); break;
        case '3': drawMode3(amplitudes); break;
        case '4': drawMode4(amplitudes); break;
        case '5': drawMode5(amplitudes); break;
    }
    ofSetColor(256);
    displayVisualizerInfo();
}
void ofApp::drawMode1(vector<float> amplitudes){
        ofFill(); // Drawn Shapes will be filled in with color
        ofSetColor(256); // This resets the color of the "brush" to white
        // ofDrawBitmapString("Rectangle Height Visualizer", 0, 15);
        ofSetColor(ofRandom(250), ofRandom(250), ofRandom(250)); 
        rectangleAmpDraw(amplitudes);
        ofSetBackgroundColor(10, 50,56);
}
void ofApp::drawMode2(vector<float> amplitudes){
        ofSetLineWidth(5); // Sets the line width
        ofNoFill(); // Only the outline of shapes will be drawn
        ofSetColor(256); // This resets the color of the "brush" to white
        // ofDrawBitmapString("Circle Radius Visualizer", 0, 15);
        int bands = amplitudes.size();
        for(int i=0; i< bands; i++){
            ofSetColor((bands - i)*32 %256,18,144); // Color varies between frequencies
            ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, amplitudes[0]/(i +1));
        }
        ofSetBackgroundColor(50, 50, 50);
}

void ofApp::drawMode3(vector<float> amplitudes){
    ofFill();  // This resets the color of the "brush" to white
    // ofDrawBitmapString("Rectangle Width Visualizer", 0, 15);
    ofSetColor(ofRandom(250), ofRandom(250), ofRandom(250));
    rectangleAmpDraw(amplitudes, true);
    ofSetBackgroundColor(200, 70, 70);
}
void ofApp::drawMode4(vector<float> amplitudes){
    if(playing) { 
        ofFill();
        // ofDrawBitmapString("Custom Visualizer", 0, 15);
        ofSetColor(ofRandom(250), ofRandom(250), ofRandom(250));
        ofDrawRectangle(ofGetWidth()/2, ofGetHeight()/2, amplitudes[0]/4+20, amplitudes[0]/4+20);
        ofDrawRectangle(ofGetWidth()/2, ofGetHeight()/2, -1*(amplitudes[0]/4+20), -1*(amplitudes[0]/4+20));
        ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, amplitudes[0]/5+20, amplitudes[0]/5+20);
        ofSetBackgroundColor(35, 0, 15);
    }
}

void ofApp::drawMode5(vector<float> amplitudes){
    
    // ofDrawBitmapString("Bonus Visualizer", 0, 15);
    if(playing) {
        ofSetLineWidth(5); 
        ofNoFill();
        int bands = amplitudes.size();
            for(int i=0; i< bands; i++){
                ofSetColor((bands - i)*32 %256,18,144);
                int enlarge = (((50)*i) + (0.1*(i+1)*amplitudes[i])); //implemented this integer to assign different sizes to every triangle
                ofDrawTriangle(ofGetWidth()/2 - enlarge, ofGetHeight()/2 + enlarge, ofGetWidth()/2 + enlarge, ofGetHeight()/2 + enlarge,ofGetWidth()/2, ofGetHeight()/2 - enlarge);
            } //Draws a triangle for every band and manipulates their respective coordinates according to the beat
    
        ofSetBackgroundColor(0, 0, 0);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // This method is called automatically when any key is pressed
    if(!replay)
    {
        keyIndex(key);
    }

    if(key != 'r' && key != 't'){recording(key);}
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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
//--------------------------------------------------------------
void ofApp::loadNewSound(string newSound){
    if(current_song != newSound) {
                sound.stop();
                sound.unload();
                sound.load(newSound);
                sound.play();
                current_song = newSound;
            }
}
//--------------------------------------------------------------
void ofApp::toggleVisualizer() {
    if(!pause) {
            pause = true;
        } else {
            pause = false;
        }
}
//--------------------------------------------------------------
void ofApp::displayVisualizerInfo() {
    // TOP LEFT VISUALIZER INFO
    ofDrawBitmapString(getCurrentMode(), 0, 15);
    if (pause) { ofDrawBitmapString("Visualizer: OFF", 0, 30);} 
    else { ofDrawBitmapString("Visualizer: ON", 0, 30); }
    ofDrawBitmapString("Current Song: " + current_song, 0, 45);
    ofDrawBitmapString("Volume: " + to_string((int)volumePercentage) + "%", 0, 60);
    std::string recordedKeys(record.begin(), record.end());
    if(rec){ ofDrawBitmapString("REC ON", 0, 75); }
    else { ofDrawBitmapString("Keys pressed: " + recordedKeys, 0, 75); } 

    // SHORCUTS ON TOP RIGHT
    ofDrawBitmapString("Use keys 1 through 5 to change modes", ofGetWidth() - 340, 15);
    ofDrawBitmapString("Use keys q, w, e & s to change song", ofGetWidth() - 340, 30);
    ofDrawBitmapString("Use keys r & t to record and replay keys", ofGetWidth() - 340, 45);
    ofDrawBitmapString("Use keys + & - to increase/decrease volume", ofGetWidth() - 340, 60);
}
//---------------------------------------------------------------
void ofApp::rectangleAmpDraw(vector<float> amplitudes) {
    for(int i = 0; i < 64; i++){
            ofDrawRectangle(ofGetWidth()/64*i, ofGetHeight(), ofGetWidth()/64,  amplitudes[i]);
        
    }
    
}
//---------------------------------------------------------------
void ofApp::rectangleAmpDraw(vector<float> amplitudes, bool sideways) {
    for(int i = 0; i < amplitudes.size(); i++){
            ofDrawRectangle(ofGetWidth(), ofGetHeight()/64*i, amplitudes[i],  ofGetHeight()/64);
        
    }
    
}
//---------------------------------------------------------------
void ofApp::recording(char input)
{
        if(rec)
        {
            record.push_back(input);

        }
}
//---------------------------------------------------------------
void ofApp::playInput(vector<char> record)
{
    if(replay)
    {

        if(tickCount % 60 == 0 && replayCounter < record.size())
        {
            keyIndex(record[replayCounter]);
            replayCounter++;
        }
        else if(replayCounter >= record.size())
        {
            replayCounter = 0;
            replay = false;
        }
    }
}
//---------------------------------------------------------------

string ofApp::getCurrentMode() {
    switch(mode) {
        case '1': return "Rectangle Height Visualizer";
        case '2': return "Circle Visualizer";
        case '3': return "Rectangle Width Visualizer";
        case '4': return "Lemon to Candy Visualizer";
        case '5': return "Bonus Visualizer: Triangle Expansion";

    }
}
//---------------------------------------------------------------
void ofApp::keyIndex(int key)
{
    switch(key){
        case 'p':
            if(playing){
                sound.stop();
            }else{
                sound.play();
            }
            playing = !playing;
            break;
        case '1':
            mode = '1';
            break;
        case '2':
            mode = '2';  
            break;
        case '3':
            mode = '3'; 
            break;
        case '4':
            mode = '4';
            break;
        case '5':
            mode = '5';
            break;
        case 'a':
            toggleVisualizer();
            break;
        case 'q':
            loadNewSound("geesebeat.wav");
            break;
        case 'w':
            loadNewSound("pigeon-coo.wav");
            break;
        case 'e':
            loadNewSound("rock-song.wav");
            break;
        case 's':
            loadNewSound("beat.wav");
            break;
        case 'r':
            if(!rec){record.clear(); rec = true;}
            else{rec = false;}
            break;
        case '=':
            if(sound.getVolume() < 1.0) {
            sound.setVolume((sound.getVolume())+0.1);
            volumePercentage += 10;
            }
            break;
        case '-':
            if(sound.getVolume() > 0.0) {
            sound.setVolume((sound.getVolume())-0.1);
            volumePercentage -= 10;
            }
            break;
        case 't':
            if(!replay && record.size() > 0)
            {replay = true; rec = false;}
            else{replay = false;}
        break;

    }
}