#include "ofMain.h"
#include "ofxMultiGLFWWindow.h"
#include "ofGLProgrammableRenderer.cpp"
#include "MurmurRendererApp.h"


//========================================================================
int main( ){
    
    //ofSetCurrentRenderer(ofGLProgrammableRenderer::TYPE);
    
    ofxMultiGLFWWindow glfw;
    glfw.setOpenGLVersion(2,1); // must be set
    //glfw.setStencilBits(8);
    
    glfw.windowCount = 2;
    
    //glfw.setMultiDisplayFullscreen(true);
    ofSetupOpenGL(&glfw,1024,768,OF_WINDOW);
    
    ofRunApp(new MurmurRendererApp());
    
}
