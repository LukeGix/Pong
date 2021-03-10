#include <SDL2/SDL.h>

struct Vector{
	float x;
	float y;
};

class Game{
	public:
		bool Initialize();
		Game();
		void Loop();
		void Shutdown();
		void GameOver();
	private:
		int R, G, B, A, Rp, Gp, Bp, Ap;
		int count;
		struct Vector mBallPos;
		struct Vector mPaddlePos;
		struct Vector mBallVelocity;
		bool lose;
		SDL_Renderer* mRenderer;
		SDL_Window* mWindow;
		void PlaySound(const char* s);
		void PlayMusic(const char* s);
		void ProcessInput();
		void UpdateGame();
		void GenerateOutput();
		bool mIsRunning;
		int mPaddleDir;
		Uint32 mTicksCount;
		
};