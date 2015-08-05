#include "ofxSecondWindow.h"

void ofxSecondWindow::setup(const char *name, int xpos, int ypos, int width, int height, bool undecorated) {
    this->width = width;
    this->height = height;
    glfwWindowHint(GLFW_DECORATED, !undecorated);
    mainWindow = glfwGetCurrentContext();
    auxWindow = glfwCreateWindow(width, height, name, NULL, mainWindow);    
    glfwSetWindowPos(auxWindow, xpos, ypos);
    
    /* enable alpha blending by default */
    glfwMakeContextCurrent(auxWindow);
    glEnable(GL_BLEND);
#ifndef TARGET_OPENGLES
    glBlendEquation(GL_FUNC_ADD);
#endif
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glfwMakeContextCurrent(mainWindow);
    glfwSetInputMode(auxWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void ofxSecondWindow::showCursor(bool show)
{
    if (show) {
        glfwSetInputMode(auxWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    else{
        glfwSetInputMode(auxWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    }
    
}

void ofxSecondWindow::begin(){
    glfwMakeContextCurrent(auxWindow);
    int width, height;
    glfwGetFramebufferSize(auxWindow, &width, &height);
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void ofxSecondWindow::end(){
    glfwSwapBuffers(auxWindow);
    glfwPollEvents();
    glfwMakeContextCurrent(mainWindow);
}

void ofxSecondWindow::show(){
    glfwShowWindow(auxWindow);
}

void ofxSecondWindow::hide(){
    glfwHideWindow(auxWindow);
}

void ofxSecondWindow::undecorate(bool undecorated)
{
    begin();
    glfwWindowHint(GLFW_DECORATED, !undecorated);
    end();
}

