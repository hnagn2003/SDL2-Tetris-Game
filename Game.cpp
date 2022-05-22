
#include "Game.h"
#include "Grid.h"
#include "Specifications.h"
#include <iostream>
#include <sstream>

TTF_Font* gFont1 = NULL;
TTF_Font* fontVarino1 = NULL;
TTF_Font* fontStar_40 = NULL;
TTF_Font* fontStar_50 = NULL;
std::vector<int> highestScore;
std::map<std::string, int> settingsElement;

Game::Game()
{
	gameState = new Game_State;
	battleProcessor = new BallteProcessor;
	gFPS_Processor = new FPS_Processor;
	helpsAndCredit = new HelpsAndCredit;
	userSettings = new UserSettings;
	tabs = -1;
}

Game::~Game()
{
    
}

void Game::init(const char* title, int xPos, int yPos, int SCREEN_WIDTH, int SCREEN_HEIGHT, bool fullscreen)
{
	bool success = true;

	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
        isRunning = false;
	}
	else
	{
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		window = SDL_CreateWindow( title, xPos, yPos, SCREEN_WIDTH, SCREEN_HEIGHT, fullscreen );
		if( window == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( renderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0 );

				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! %s\n", IMG_GetError() );
					success = false;
				}
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
				SDL_SetHint (SDL_HINT_WINDOWS_DISABLE_THREAD_NAMING, "1");
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }
			}
		}

        isRunning = true;
	}

	if( !success )
	{
		printf( "Failed to initialize!\n" );
	}
	
	gFPS_Processor->initTimeCounting();

}
void Game::loadmedia()
{
	loadGameFonts();
	tabs_menu.setUpMenu(renderer);
	helpsAndCredit->setUp(renderer);
	userSettings->initSettings(renderer); 

	loadGameButtons(renderer);
	playingSoundtrack = Mix_LoadMUS( "assets/Musics/playing.mp3" );
	themeSoundtrack = Mix_LoadMUS( "assets/Musics/backgroundMusic.mp3" );
	ES_MouseClick = Mix_LoadWAV(ES_MouseClickP.c_str());
	se_move = Mix_LoadWAV(se_moveP.c_str());
	se_hold = Mix_LoadWAV(se_holdP.c_str());
	se_drop = Mix_LoadWAV(se_dropP.c_str());
	se_start = Mix_LoadWAV(se_startP.c_str());
	se_double = Mix_LoadWAV(se_doubleP.c_str());
	se_pause = Mix_LoadWAV(se_pauseP.c_str());
	se_rotate = Mix_LoadWAV(se_rotateP.c_str());
	se_count = Mix_LoadWAV(se_countP.c_str());
	me_gameover = Mix_LoadMUS(me_gameoverP.c_str());
	se_gameover = Mix_LoadWAV(se_gameoverP.c_str());
	for (int i=0; i<4; i++)
	{
		se_lineCompleted[i] = Mix_LoadWAV(se_lineCompletedP[i].c_str());
	}
	if( ES_MouseClick == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
	}
	settingsElement.insert(std::make_pair("Ghost Piece", 1));
	settingsElement.insert(std::make_pair("Level", easy));
	settingsElement.insert(std::make_pair("Sound Effects", 1));
	settingsElement.insert(std::make_pair("Music Volume", 80));



	SDL_RWops* settingsFile = SDL_RWFromFile("settings/settings.bin", "r+b");
	if (settingsFile==NULL){
		settingsFile = SDL_RWFromFile("settings/settings.bin", "w+b");
		if (settingsFile!=NULL){
			for (auto it = settingsElement.begin(); it!=settingsElement.end(); it++){
				SDL_RWwrite(settingsFile, &(it->second), sizeof(int), 1);			
			}
			SDL_RWclose( settingsFile );
		}else{
			printf( "Error: Unable to create file! SDL Error: %s\n", SDL_GetError() );
		}

	}else{
		for (auto it = settingsElement.begin(); it!=settingsElement.end(); it++){
			SDL_RWread(settingsFile, &(it->second), sizeof(int), 1);
		}
		SDL_RWclose(settingsFile);
	}

	highestScore.insert(highestScore.end(), scoreMaxMem, 0);
	SDL_RWops* highestScoreFile = SDL_RWFromFile("settings/scoreFile.bin", "r+b");
	if (highestScoreFile==NULL){
		highestScoreFile = SDL_RWFromFile("settings/scoreFile.bin", "w+b");
		if (highestScoreFile!=NULL){
			for (int i=0; i<scoreMaxMem; i++){
				SDL_RWwrite(highestScoreFile, &(highestScore[i]), sizeof(int), 1);			
			}
			SDL_RWclose( highestScoreFile );
		}else{
			printf( "Error: Unable to create file! SDL Error: %s\n", SDL_GetError() );
		}
	}else{
		for (int i=0; i<scoreMaxMem; i++){
			SDL_RWread(highestScoreFile, &(highestScore[i]), sizeof(int), 1);
		}
		SDL_RWclose(highestScoreFile);
	}
}
void Game::handleEvents()							
{

        SDL_Event event; 
		while(SDL_PollEvent(&event)){
			
			switch (event.type)
			{
				case SDL_QUIT:
					isRunning = false;
					break;
                case SDL_KEYDOWN:
					switch ( event.key.keysym.sym )
					{
					case SDLK_ESCAPE: //...
						isRunning = false;
						break;
					
					default:
						break;
					}
				default:
					switch (tabs)
					{
					case Menu:
						tabs_menu.handleEvents(&event);
						tabs = tabs_menu.getDirect();
						break;
					case InGame_SoloMode:
						gameState->handleEvent(event);
						tabs = gameState->getDirect();
						break;
					case InGame_BattleMode:
						battleProcessor->handleEvent(event);
						tabs = battleProcessor->getDirect();
						break;
					case Helps:
						helpsAndCredit->handleEvent(&event);
						tabs = helpsAndCredit->getDirect();
						break;
					case Settings:
						userSettings->handleEvents(&event);
						tabs = userSettings->getDirect();
						break;
					default:
						break;
					}
					break;
			}
		}
} 
void Game::playMusic()
{

	switch (tabs)
	{
	case InGame_SoloMode:
		if( Mix_PlayingMusic() == 0 && !gameState->isInCountDown() && gameState->getPlaying())
		{
			Mix_PlayMusic( playingSoundtrack, -1 );
		}
		if (gameState->getPause() && gameState->getPlaying())
		{
			Mix_HaltMusic();
		}
		break;
	case InGame_BattleMode:
		if( Mix_PlayingMusic() == 0 && !battleProcessor->getGameState1()->isInCountDown() && battleProcessor->getGameState1()->getPlaying())
		{
			Mix_PlayMusic( playingSoundtrack, -1 );
		}
		if (battleProcessor->getGameState1()->getPause() && battleProcessor->getGameState1()->getPlaying())
		{
			Mix_HaltMusic();
		}
		break;
	default:
		if( Mix_PlayingMusic() == 0 ){
			Mix_PlayMusic( themeSoundtrack, -1 );
		}
		break;
	}
}
void Game::update()
{
	Mix_VolumeMusic(settingsElement["Music Volume"]);
	gFPS_Processor->cappingFrame();
	switch (tabs){
		case Menu:
			gameState->reset();
			break;
		case InGame_SoloMode:
			if (!gameState->getOver()){
				backButton->setCenterPosition(100, 100);
			}else{
				replayButton->setCenterPosition(1137, 569);
				backButton->setCenterPosition(1289, 569);
				if (!gameState->getRecord()){
					updateScoreTable(gameState->getScore());
					gameState->setRecord(1);
				}
				Mix_HaltMusic();
			}
			gameState->update();
			break;
		case InGame_BattleMode:
			if (!battleProcessor->getOver()){
				backButton->setCenterPosition(100, 100);
			}else{
				replayButton->setCenterPosition(SCREEN_WIDTH/2-70, 655);
				backButton->setCenterPosition(SCREEN_WIDTH/2+120, 655);
				Mix_HaltMusic();
			}
			battleProcessor->update();
			break;

		case Helps:
			backButton->setCenterPosition(100, 100);
			break;
		case Settings:
			backButton->setCenterPosition(100, 100);
			userSettings->update();
			break;
		default:
			break;
	}

}

void Game::render()
{
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0 );
    SDL_RenderClear(renderer);
	static LTexture backGround {backGroundPicture, renderer};
	backGround.render(renderer, 0, 0);
	
	switch (tabs)
	{
	case Menu:
		tabs_menu.render(renderer);
		break;
	case InGame_SoloMode:
		gameState->render(renderer);
		break;
	case InGame_BattleMode:
		battleProcessor->render(renderer);
		break;

	case Helps:
		helpsAndCredit->render(renderer);
		break;
	case Settings:
		userSettings->render(renderer);
		break;
	default:
		break;
	}
    SDL_RenderPresent(renderer);

}

void Game::clean()
{
	SDL_RWops* settingsFile = SDL_RWFromFile("settings/settings.bin", "w+b");
	for (auto it = settingsElement.begin(); it!=settingsElement.end(); it++){
		SDL_RWwrite(settingsFile, &(it->second), sizeof(int), 1);			
	}
	SDL_RWops* highestScoreFile = SDL_RWFromFile("settings/scoreFile.bin", "w+b");
	for (int i=0; i<scoreMaxMem; i++){
		SDL_RWwrite(highestScoreFile, &(highestScore[i]), sizeof(int), 1);			
	}
	SDL_RWclose( highestScoreFile );
	SDL_RWclose( settingsFile );
	TTF_CloseFont( gFont1 );
	gFont1 = NULL;
    SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	window = NULL;
	renderer = NULL;
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}