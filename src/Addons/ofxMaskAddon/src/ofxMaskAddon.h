#pragma once

#include "ofFbo.h"
#include "ofShader.h"

class ofxMaskAddon
{
public:

	enum Type
	{
		ALPHA,
		LUMINANCE
	};
    
    ofxMaskAddon() {}
    
	void setup(int width, int height, Type type);
	int getWidth() { return width_; }
	int getHeight() { return height_; }

	void beginMask(bool clear=true);
	void endMask();
	void clearMask();

	void begin(bool clear=true);
	void end();

	void draw();
	
	void drawMasker();
	void drawMaskee();

	ofTexture& getMaskerTextureReference() { return masker_.getTextureReference(); }
	ofTexture& getMaskeeTextureReference() { return maskee_.getTextureReference(); }

private:
	ofFbo masker_, maskee_;
	ofShader shader_;
	float vertices_[8];
	float tex_coords_[8];
	float width_, height_;
};

/* EOF */