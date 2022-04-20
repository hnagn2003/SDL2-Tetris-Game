#include <SDL_image.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <algorithm>  
#include <stdio.h>
#include "Structure.h"

LTexture::LTexture()
{
	// mTexture = NULL;
	// mWidth = 0;
	// mHeight = 0;
}

LTexture::~LTexture()
{
	// free();
}

bool LTexture::loadFromFile( std::string path, SDL_Renderer* gRenderer)
{
	// free();

	// SDL_Texture* newTexture = NULL;

	// SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	// if( loadedSurface == NULL )
	// {
	// 	printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	// }
	// else
	// {
	// 	SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

    //     newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
	// 	if( newTexture == NULL )
	// 	{
	// 		printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
	// 	}
	// 	else
	// 	{
	// 		mWidth = loadedSurface->w;
	// 		mHeight = loadedSurface->h;
	// 	}

	// 	SDL_FreeSurface( loadedSurface );
	// }
    // mTexture = newTexture;
	// return (mTexture!=NULL);
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor, TTF_Font* gFont, SDL_Renderer* gRenderer )
{
	// free();

	// SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	// if( textSurface != NULL )
	// {
    //     mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
	// 	if( mTexture == NULL )
	// 	{
	// 		printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
	// 	}
	// 	else
	// 	{
	// 		mWidth = textSurface->w;
	// 		mHeight = textSurface->h;
	// 	}

	// 	SDL_FreeSurface( textSurface );
	// }
	// else
	// {
	// 	printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	// }

	
	// return mTexture != NULL;
}
#endif

void LTexture::free()
{
	// if( mTexture != NULL )
	// {
	// 	SDL_DestroyTexture( mTexture );
	// 	mTexture = NULL;
	// 	mWidth = 0;
	// 	mHeight = 0;
	// }
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	// SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
	// SDL_SetTextureBlendMode( mTexture, blending );
}
		
void LTexture::setAlpha( Uint8 alpha )
{
	// SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render(SDL_Renderer* gRenderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	// SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	// if( clip != NULL )
	// {
	// 	renderQuad.w = clip->w;
	// 	renderQuad.h = clip->h;
	// }

	// SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth()
{
	// return mWidth;
}

int LTexture::getHeight()
{
	// return mHeight;
}


LTimer::LTimer()
{
    // mStartTicks = 0;
    // mPausedTicks = 0;

    // mPaused = false;
    // mStarted = false;
}

void LTimer::start()
{
    // mStarted = true;

    // mPaused = false;

    // mStartTicks = SDL_GetTicks();
	// mPausedTicks = 0;
}

void LTimer::stop()
{
    // mStarted = false;

    // mPaused = false;

	// mStartTicks = 0;
	// mPausedTicks = 0;
}

void LTimer::pause()
{
    // if( mStarted && !mPaused )
    // {
    //     mPaused = true;

    //     mPausedTicks = SDL_GetTicks() - mStartTicks;
	// 	mStartTicks = 0;
    // }
}

void LTimer::unpause()
{
    // if( mStarted && mPaused )
    // {
    //     mPaused = false;

    //     mStartTicks = SDL_GetTicks() - mPausedTicks;

    //     mPausedTicks = 0;
    // }
}

Uint32 LTimer::getTicks()
{
	// Uint32 time = 0;

    // if( mStarted )
    // {
    //     if( mPaused )
    //     {
    //         time = mPausedTicks;
    //     }
    //     else
    //     {
    //         time = SDL_GetTicks() - mStartTicks;
    //     }
    // }

    // return time;
}

bool LTimer::isStarted()
{
    // return mStarted;
}

bool LTimer::isPaused()
{
    // return mPaused && mStarted;
}