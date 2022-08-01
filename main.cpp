#include <iostream>

#include "SDL.h"
#include "SDL_ttf.h"

#include "CustomText.h"
#include "CustomRectangle.h"


#define WINDOW_WIDTH	800
#define WINDOW_HEIGHT	600

#define PADDLE_MAX_VELOCITY 1000
#define BALL_MAX_X_VELOCITY 500
#define BALL_MAX_Y_VELOCITY 250

#define FPS 150
#define FRAME_TARGET_TIME (1000/FPS)

enum class GameScreen {
	GAME_START_SCREEN,
	GAME_PLAY_SCREEN,
	GAME_OVER_SCREEN
};


int lastFrameTime = 0;
float timeToWait = 0;
float deltaTime = 0;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Rect rendererRect;


GameScreen screenContext = GameScreen::GAME_START_SCREEN;
bool runGameLoop = true;
bool isGameFirstStartOrGameReset = true;
std::string scoreText = "";
Uint32 scoreCount = 0;

CustomRectangle paddle, ball;
SDL_Rect paddleRect, ballRect;
CustomText customScoreText, pressAnyKeyText, gameOverText, pressRText;
SDL_Rect customScoreTextRect, pressAnyKeyTextRect, gameOverTextRect, pressRTextRect;


void setup();
void processInput();
void update();
void render();
bool GameInit();
void GameDeInit();
void screenBlackOut(SDL_Renderer* renderer);


void setup() {

	if (screenContext == GameScreen::GAME_START_SCREEN) {

		scoreCount = 0;
		SDL_RenderClear(renderer);
		screenBlackOut(renderer);

		// Display -> paddle
		paddle = CustomRectangle(renderer, 0, WINDOW_HEIGHT-50, 150, 5, 0);
		paddle.renderRectangle();
		paddle.setCenteredHorizontally(WINDOW_WIDTH, WINDOW_HEIGHT);
		paddle.renderRectangle();
		paddleRect = paddle.getRect();
		SDL_RenderFillRect(renderer, &paddleRect);

		// Display -> ball
		ball = CustomRectangle(renderer, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 10, 10, 5);
		ball.renderRectangle();
		ball.setX( (paddle.getX() + paddle.getW()/2) - ball.getW()/2 );
		ball.setY(paddle.getY() - 2*ball.getH());
		ballRect = ball.getRect();
		SDL_RenderFillRect(renderer, &ballRect);

		// Display -> score text
		scoreText = "Score : ";
		customScoreText = CustomText(renderer, scoreText, SDL_Color{ 255,255,255,255 });
		customScoreText.renderText();
		customScoreTextRect = customScoreText.getRect();
		SDL_RenderCopy(renderer, customScoreText.getTexture(), NULL, &customScoreTextRect);

		// Display -> Press any key text
		pressAnyKeyText = CustomText(renderer, "Press any key to play", 30, SDL_Color{ 255,255,255,255 });
		pressAnyKeyText.renderText();
		pressAnyKeyText.setCentered(WINDOW_WIDTH, WINDOW_HEIGHT);
		pressAnyKeyText.renderText();
		pressAnyKeyTextRect = pressAnyKeyText.getRect();
		SDL_RenderCopy(renderer, pressAnyKeyText.getTexture(), NULL, &pressAnyKeyTextRect);
		
		SDL_RenderPresent(renderer);
		return;
	}

	if (screenContext == GameScreen::GAME_PLAY_SCREEN) {

		ball.setVelX(BALL_MAX_X_VELOCITY);
		ball.setVelY(BALL_MAX_Y_VELOCITY);
		return;
	}

	if (screenContext == GameScreen::GAME_OVER_SCREEN) {

		// Display -> Game over text
		gameOverText = CustomText(renderer, "Game Over", 30, SDL_Color{ 255,255,255,255 });
		gameOverText.renderText();
		gameOverText.setCentered(WINDOW_WIDTH, WINDOW_HEIGHT);
		gameOverText.renderText();
		gameOverTextRect = gameOverText.getRect();
		SDL_RenderCopy(renderer, gameOverText.getTexture(), NULL, &gameOverTextRect);

		// Display -> Game over text
		pressRText = CustomText(renderer, "Press 'R' to restart game", 20, SDL_Color{ 255,255,255,255 });
		pressRText.renderText();
		pressRText.setCentered(WINDOW_WIDTH, WINDOW_HEIGHT + 2*gameOverText.getRect().h);
		pressRText.renderText();
		pressRTextRect = pressRText.getRect();
		SDL_RenderCopy(renderer, pressRText.getTexture(), NULL, &pressRTextRect);

		

		SDL_RenderPresent(renderer);
		return;
	}
}


void processInput() {

	SDL_Event ev;
	SDL_PollEvent(&ev);

	if (screenContext == GameScreen::GAME_START_SCREEN) {

		switch (ev.type) {

		case SDL_KEYDOWN:
			if (ev.key.keysym.sym == SDLK_ESCAPE) {
				runGameLoop = false;
				break;
			}
			screenContext = GameScreen::GAME_PLAY_SCREEN;
			isGameFirstStartOrGameReset = true;
			break;

		default:
			break;

		}

		return;
	}

	if (screenContext == GameScreen::GAME_PLAY_SCREEN) {

		switch (ev.type) {

		case SDL_KEYDOWN:
			if (ev.key.keysym.sym == SDLK_ESCAPE) {
				runGameLoop = false;
				break;
			}
			if (ev.key.keysym.sym == SDLK_UP) {
				paddle.setVelY(PADDLE_MAX_VELOCITY);
			}
			if (ev.key.keysym.sym == SDLK_DOWN) {
				paddle.setVelY(-PADDLE_MAX_VELOCITY);
			}
			if (ev.key.keysym.sym == SDLK_LEFT) {
				paddle.setVelX(-PADDLE_MAX_VELOCITY);
			}
			if (ev.key.keysym.sym == SDLK_RIGHT) {
				paddle.setVelX(PADDLE_MAX_VELOCITY);
			}

			break;

		case SDL_KEYUP:
			if (ev.key.keysym.sym == SDLK_UP) {
				paddle.setVelY(0);
			}
			if (ev.key.keysym.sym == SDLK_DOWN) {
				paddle.setVelY(0);
			}
			if (ev.key.keysym.sym == SDLK_LEFT) {
				paddle.setVelX(0);
			}
			if (ev.key.keysym.sym == SDLK_RIGHT) {
				paddle.setVelX(0);
			}

			break;

		default:
			break;

		}
		return;
	}

	if (screenContext == GameScreen::GAME_OVER_SCREEN) {

		switch (ev.type) {

		case SDL_KEYDOWN:
			if (ev.key.keysym.sym == SDLK_ESCAPE) {
				runGameLoop = false;
				break;
			}
			if (ev.key.keysym.sym == SDLK_r) {
				screenContext = GameScreen::GAME_START_SCREEN;
				isGameFirstStartOrGameReset = true;
			}
			break;

		default:
			break;

		}
		return;
	}
}


void update() {

	timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - lastFrameTime);
	if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME)
		SDL_Delay(timeToWait);

	deltaTime = (SDL_GetTicks() - lastFrameTime) / 1000.0f;
	lastFrameTime = SDL_GetTicks();

	if (screenContext == GameScreen::GAME_START_SCREEN) {
		
		return;
	}
	if (screenContext == GameScreen::GAME_PLAY_SCREEN) {

		// Ball action
		ball.setX(ball.getX() + (ball.getVelX() * deltaTime));
		ball.setY(ball.getY() + (ball.getVelY() * deltaTime));

		if (ball.getX() <= 0)
			ball.setVelX(-ball.getVelX());
		if (ball.getX() >= WINDOW_WIDTH)
			ball.setVelX(-ball.getVelX());
		if (ball.getY() <= 0)
			ball.setVelY(-ball.getVelY());
		if (ball.getY() >= WINDOW_HEIGHT) {
			screenContext = GameScreen::GAME_OVER_SCREEN;
			isGameFirstStartOrGameReset = true;
		}

		// Paddle action
		paddle.setX( paddle.getX() + (paddle.getVelX() * deltaTime) );
		if (paddle.getX() <= 0)
			paddle.setX(0);
		if (paddle.getX() + paddle.getW() >= WINDOW_WIDTH)
			paddle.setX(WINDOW_WIDTH - paddle.getW());


		// When ball hits paddle
		if (paddle.hasCollidedUp(ball)) {
			ball.setVelY(-ball.getVelY());
			scoreText = "Score : " + std::to_string(++scoreCount);
		}
		if (paddle.hasCollidedDown(ball)) {
			ball.setVelY(-ball.getVelY());
			scoreText = "Score : " + std::to_string(++scoreCount);
		}
		if (paddle.hasCollidedLeft(ball)) {
			ball.setVelX(-ball.getVelX());
			scoreText = "Score : " + std::to_string(++scoreCount);
		}
		if (paddle.hasCollidedRight(ball)) {
			ball.setVelX(-ball.getVelX());
			scoreText = "Score : " + std::to_string(++scoreCount);
		}

		return;
	}
	if (screenContext == GameScreen::GAME_OVER_SCREEN) {

		return;
	}
}
void render() {
	if (screenContext == GameScreen::GAME_START_SCREEN) {

		return;
	}
	if (screenContext == GameScreen::GAME_PLAY_SCREEN) {
		
		SDL_RenderClear(renderer);

		// Display -> Black screen
		screenBlackOut(renderer);

		// Display -> ball
		ball.renderRectangle();
		ballRect = ball.getRect();
		SDL_RenderFillRect(renderer, &ballRect);

		// Display -> paddle
		paddle.renderRectangle();
		paddleRect = paddle.getRect();
		SDL_RenderFillRect(renderer, &paddleRect);

		// Display -> score text
		customScoreText.setText(scoreText);
		customScoreText.renderText();
		customScoreTextRect = customScoreText.getRect();
		SDL_RenderCopy(renderer, customScoreText.getTexture(), NULL, &customScoreTextRect);

		SDL_RenderPresent(renderer);
		return;
	}
	if (screenContext == GameScreen::GAME_OVER_SCREEN) {

		return;
	}
}




bool GameInit() {

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cerr << "Error SDL_Init() in GameInit()" << std::endl;
		return false;
	}

	if (TTF_Init() == -1) {
		std::cerr << "Error TTF_Init() in GameInit()" << std::endl;
		return false;
	}

	window = SDL_CreateWindow(
		"PingPong",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_BORDERLESS
	);
	if (window == NULL) {
		std::cerr << "Error SDL_CreateWindow() in GameInit()" << std::endl;
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == NULL) {
		std::cerr << "Error SDL_CreateRenderer() in GameInit()" << std::endl;
		return false;
	}

	rendererRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
}


void GameDeInit() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
}


void screenBlackOut(SDL_Renderer* renderer) {
	SDL_Rect tempRendererRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, &tempRendererRect);
}


int main(int argc, char* argv[]) {
	
	runGameLoop = GameInit();

	do {

		if (isGameFirstStartOrGameReset) {
			setup();
			isGameFirstStartOrGameReset = false;
		}
		processInput();
		update();
		render();

	} while(runGameLoop);
	
	return 0;
}