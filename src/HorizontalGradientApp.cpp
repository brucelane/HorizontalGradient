#include "cinder/ImageIo.h"
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/GlslProg.h"
#include "cinder/gl/Texture.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class HorizontalGradientApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
  private:
	gl::Texture		mTexture0;
	gl::Texture		mTexture1;
	Vec3i			iResolution;
	float			iGlobalTime;
	gl::GlslProg	mShader;
};

void HorizontalGradientApp::setup()
{
	try {
		// load the two textures
		mTexture0 = gl::Texture( loadImage( loadAsset("bottom.jpg") ) );
		mTexture1 = gl::Texture( loadImage( loadAsset("top.jpg") ) );
		iResolution = Vec3i(1024, 748, 1);
		iGlobalTime = 1;
		// load and compile the shader
		mShader = gl::GlslProg( loadAsset("horiz_vert.glsl"), loadAsset("horiz_frag.glsl") );
	}
	catch( const std::exception &e ) {
		// if anything went wrong, show it in the output window
		console() << e.what() << std::endl;
	}
}

void HorizontalGradientApp::mouseDown( MouseEvent event )
{
}

void HorizontalGradientApp::update()
{
	iGlobalTime = getElapsedSeconds();
}

void HorizontalGradientApp::draw()
{
		// clear the window
	gl::clear();

	// bind the shader and tell it which texture units to use (see: shader_frag.glsl)
	mShader.bind();
	mShader.uniform("tex0", 0);	
	mShader.uniform("tex1", 1);
	mShader.uniform("iResolution", iResolution);
	mShader.uniform("iGlobalTime", iGlobalTime);

	// enable the use of textures
	gl::enable( GL_TEXTURE_2D );

	// bind them
	mTexture0.bind(0);
	mTexture1.bind(1);

	// now run the shader for every pixel in the window
	// by drawing a full screen rectangle
	gl::drawSolidRect( Rectf( getWindowBounds() ), false );

	// unbind textures and shader
	mTexture1.unbind();
	mTexture0.unbind();
	mShader.unbind();
}

CINDER_APP_BASIC( HorizontalGradientApp, RendererGl )
