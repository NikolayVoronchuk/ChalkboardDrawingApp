#include "cinder/app/AppBasic.h"
#include <list>
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "Resources.h"


using namespace ci;
using namespace ci::app;
using namespace std;


class DrawingApp : public AppBasic {
  public:
	void prepareSettings( Settings *settings );
	void mouseDrag( MouseEvent event );
	void keyDown( KeyEvent event );
	void draw();
	void setup();

	// List of points between which line supposed to be drawn

	list<Vec2f>		mPoints;
	gl::Texture mImage;
	
};

// Setting window size at 800 by 600

void DrawingApp::prepareSettings( Settings *settings )
{
	settings->setWindowSize( 800, 600 );
}

void DrawingApp::setup()
{
	mImage = gl::Texture( loadImage( loadResource( RES_MY_RES ) ) );
}


// Implementation of drawing function

void DrawingApp::mouseDrag( MouseEvent event )
{
	mPoints.push_back( event.getPos() );
}

// Key options: F = Full Screen, X = Clear Canvas

void DrawingApp::keyDown( KeyEvent event )
{

	if( event.getChar() == 'f' )
		setFullScreen( ! isFullScreen() );
	else if( event.getChar() == 'x' )
		mPoints.clear();
}


void DrawingApp::draw()
{

	mImage.enableAndBind();	
	gl::draw( mImage, getWindowBounds() );

	gl::begin( GL_QUAD_STRIP );
	for( auto pointIter = mPoints.begin(); pointIter != mPoints.end(); ++pointIter ) {
		gl::vertex( *pointIter );
	}
	gl::end();
}


CINDER_APP_BASIC( DrawingApp, RendererGl )