#include "Game.h"
#include <iostream>
#include <math.h>
#include <SDL2/SDL_mixer.h>
using namespace std;
Game::Game(){
	mPaddlePos.x = 512;
	mPaddlePos.y = 384;

	mBallPos.x = 512;
	mBallPos.y = 384;

	mTicksCount = 0;
	mPaddleDir = 0;
	mBallVelocity.x = -200.0f;
	mBallVelocity.y = 235.0f;
	R = G = B = A = Rp = Gp = Bp = Ap = 255;
	count = 0;
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2024);
}

void Game::PlayMusic(const char* s){
	Mix_Music* music = Mix_LoadMUS(s);
	if(Mix_PlayMusic(music, -1) < 0){
		std::cout << "Errore!" << Mix_GetError(); 
	}
}

void Game::PlaySound(const char* s){

	Mix_Chunk* effect = Mix_LoadWAV(s);
	if(Mix_PlayChannel(1, effect, 0) < 0){
		std::cout << "Errore!" << Mix_GetError(); 
	}
}



void Game::UpdateGame(){
	while(!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

	if(deltaTime > 0.05f){
		deltaTime = 0.05f;
	}

	mTicksCount = SDL_GetTicks();

	//Aggiorno gli oggetti
	if(mPaddleDir != 0){
		mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;
		mPaddleDir = 0;
	}

	//Devo evitare che il paddle esca fuori dallo schermo --> come faccio?
	//Se la posizione del paddle è minore

	if(mPaddlePos.y < 55){
		mPaddlePos.y = 55;
	}
	else if(mPaddlePos.y > 713){
		mPaddlePos.y = 713;
	}

	mBallPos.x += mBallVelocity.x * deltaTime;
	mBallPos.y += mBallVelocity.y * deltaTime;

	if(mBallPos.x <= 20){
		mIsRunning = false;
		lose = true;
		mBallVelocity.x *= -1;
	}
	if((mBallPos.x >= 1004.0f) && (mBallVelocity.x > 0.0f)){
		Game::PlaySound("Sound/bounce.wav");
		mBallVelocity.x *= -1;
		if(R == 255){
			R = 30;
		}else{
			R += 20;
		}
		if(G == 255){
			G = 0;
		}else{
			G += 20;
		}
		if(B == 255){
			B = 30;
		}else{
			B += 20;
		}
		if(A == 255){
			A = 100;
		}else{
			A += 20;
		}

	}
	if(mBallPos.y <= 20 && mBallVelocity.y < 0.0f){
		Game::PlaySound("Sound/bounce.wav");
		mBallVelocity.y *= -1;
		if(R == 255){
			R = 30;
		}else{
			R += 20;
		}
		if(G == 255){
			G = 0;
		}else{
			G += 20;
		}
		if(B == 255){
			B = 30;
		}else{
			B += 20;
		}
		if(A == 255){
			A = 100;
		}else{
			A += 20;
		}
	}
	if(mBallPos.y >= 748 && mBallVelocity.y > 0.0f){
		Game::PlaySound("Sound/bounce.wav");
		mBallVelocity.y *= -1;
		if(R == 255){
			R = 30;
		}else{
			R += 20;
		}
		if(G == 255){
			G = 0;
		}else{
			G += 20;
		}
		if(B == 255){
			B = 30;
		}else{
			B += 20;
		}
		if(A == 255){
			A = 100;
		}else{
			A += 20;
		}
	}

	float diff = mPaddlePos.y - mBallPos.y;
	// Take absolute value of difference
	diff = (diff > 0.0f) ? diff : -diff;
	if (
		// Our y-difference is small enough
		diff <= 35 &&
		// We are in the correct x-position
		mBallPos.x <= 25.0f && mBallPos.x >= 20.0f &&
		// The ball is moving to the left
		mBallVelocity.x < 0.0f)
	{	
		Game::PlaySound("Sound/bounce.wav");
		mBallVelocity.x *= -1.0f;
		if(R == 255){
			R = 30;
		}else{
			R += 20;
		}
		if(G == 255){
			G = 0;
		}else{
			G += 20;
		}
		if(B == 255){
			B = 30;
		}else{
			B += 20;
		}
		if(A == 255){
			A = 100;
		}else{
			A += 20;
		}
		count++;
		if((count % 5) == 0){
			Rp = 255;
			Gp = 0;
			Bp = 0;
			Ap = 255;
		}else{
			Rp = Gp = Bp = Ap = 255;
		}
	}

}


bool Game::Initialize(){
	int sdlResult = (SDL_Init(SDL_INIT_VIDEO)); 
	if(sdlResult != 0){
		std::cout << "Errore!" << std::endl;
		return false;
	}

	if(!(mWindow = SDL_CreateWindow("My first game - PONG", 100, 100, 1024, 768, SDL_WINDOW_RESIZABLE))){
		std::cout << "Error!" << std::endl;
		return false;
	}
	if(!(mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))){
		std::cout << "Error!" << std::endl;
		return false;
	}

	int sdlResultAudio = (SDL_Init(SDL_INIT_AUDIO)); 
	if(sdlResult != 0){
		std::cout << "Errore Audio!" << std::endl;
		return false;
	}

	lose = false;
	mIsRunning = true;
	SDL_Delay(1000);
	return true;
}

void Game::ProcessInput(){
	SDL_Event event;
	const Uint8* state = SDL_GetKeyboardState(NULL);	//è di tipo const Uint8*
	while(SDL_PollEvent(&event)){
		switch(event.type){
			//In base al tipo di evento, lo gestisco in modo diverso

			case SDL_QUIT:
				mIsRunning = false;
				std::cout << "Closing..." << std::endl;
				break;
		}
	}

	if(state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP]){
		mPaddleDir -= 1;
	}

	if(state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN]){
		mPaddleDir += 1;
	}

	if(state[SDL_SCANCODE_ESCAPE]){	//Se premo esc
		mIsRunning = false;
	}

	/*if(state[SDL_SCANCODE_SPACE]){
		mBallVelocity.x = 0;
		mBallVelocity.y = 0;

	}*/
}

void Game::GenerateOutput(){
	//Creo un SDL_Rect oggetto
	SDL_Rect Ball{
		(int)(mBallPos.x - 15/2),	//x --> distanza dal margine sinistro dello schermo
		(int)(mBallPos.y - 15/2),	//y --> distanza dal margine superiore dello schermo
		15,
		15
	};

	SDL_Rect Paddle{
		10,
		(int)(mPaddlePos.y - 70/2),
		15,
		70
	};

	SDL_SetRenderDrawColor(mRenderer, 0, 190, 0, 255);
	SDL_RenderClear(mRenderer);
	//Disegno qualcosa...
	SDL_SetRenderDrawColor(mRenderer, Rp, Gp, Bp, Ap);	//Bianco
	SDL_RenderFillRect(mRenderer, &Paddle);
	SDL_SetRenderDrawColor(mRenderer, R, G, B, A);
	SDL_RenderFillRect(mRenderer, &Ball);
	SDL_RenderPresent(mRenderer);
}

void Game::Shutdown(){
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	SDL_Quit();
}

void Game::GameOver(){
	std::cout << "Game Over!" << std::endl;
	SDL_Delay(1500);
}
void Game::Loop(){
	while((mIsRunning == true) && (lose == false)){
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}

	if(lose == true){
		Game::GameOver();
	}
}