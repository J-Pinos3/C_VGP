/*
	'SIMPLE'... sure bro
	Simple Game with C programming languaje and the SDL library
	I made this game with this guy's youtube Videos: VertoStudio3D

	Current min: 0:00 of video
	'Learn Game Programming in C Episode 11 - Collision detection Pt2'
*/

#include "SDL.H"
#include "SDL_image.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define GRAVITY 0.32f

typedef struct {
	float x, y;
	float dy;
	short life;
	int onLedge;
	char* name;
} Man;


typedef struct {
	int x, y;
} Star;


typedef struct {
	int x, y, w, h;
} Ledge;


typedef struct {
	//PLAYERS
	Man man;
	
	//STARS
	Star stars[100];

	//LEDGES
	Ledge ledges[100];

	//IMAGES
	SDL_Texture* star;
	SDL_Texture* manFrames[2];
	SDL_Texture* brick;

	//RENDERER
	SDL_Renderer* renderer;
} GameState;


void loadGame(GameState* game) {
	SDL_Surface* surface = NULL;

	surface = IMG_Load("star1.png");
	if (surface == NULL) {
		printf("Cannot find star1.png");
		SDL_Quit();
		exit(1);
	}
	game->star = SDL_CreateTextureFromSurface(game->renderer, surface);
	SDL_FreeSurface(surface);


	surface = IMG_Load("stand_man.png");
	if (surface == NULL) {
		printf("Cannot find stand_man.png");
		SDL_Quit();
		exit(1);
	}
	game->manFrames[0] = SDL_CreateTextureFromSurface(game->renderer, surface);
	SDL_FreeSurface(surface);


	surface = IMG_Load("kick_man.png");
	if (surface == NULL) {
		printf("Cannot find kick_man.png");
		SDL_Quit();
		exit(1);
	}
	game->manFrames[1] = SDL_CreateTextureFromSurface(game->renderer, surface);
	SDL_FreeSurface(surface);


	surface = IMG_Load("brick.png");
	game->brick = SDL_CreateTextureFromSurface(game->renderer, surface);
	SDL_FreeSurface(surface);

	game->man.x = 320 - 40;
	game->man.y = 240 - 40;
	game->man.dy = 0;
	game->man.onLedge = 0;

	//initialize stars
	for (int i = 0; i < 100; i++) {
		game->stars[i].x = rand() % 640;//numbers bwtween 0 and (width|height)exclusive
		game->stars[i].y = rand() % 480;
	}

	//initialize ledges
	for (int i = 0; i < 100; i++) {
		game->ledges[i].w = 120;//88 x 22  w=256 h=64
		game->ledges[i].h = 24;
		game->ledges[i].x = i*120;
		game->ledges[i].y = 400;
	}
	game->ledges[99].x = 350;
	game->ledges[99].y = 200;
}


int collide2d(float x1, float y1, float x2, float y2, float wt1, float ht1, float wt2, float ht2) {
	return  !( ( (x1 > (x2+wt2)) || (x2 > (x1+wt1)) ) || ( (y1 > (y2 + ht2)) || (y2 > (y1+ht1)) ) ) ;
}

void process(GameState *game) {
	Man* man = &game->man;
	man->y += man->dy;
	
	man->dy += GRAVITY;
}

void collisionDetect(GameState *game) {
	for (int i = 0; i < 100; i++) {
		float mw = 50, mh = 50;
		float mx = game->man.x, my = game->man.y;
		float bx = game->ledges[i].x, by = game->ledges[i].y, bw = game->ledges[i].w, bh = game->ledges[i].h;

		if ( ((my + mh) > by) && (my < (by+bh)) ) {
			// rubbing against right edge
			if(  (mx < (bx+bw)) && ((mx+mw)>(mx+bw))  ){
				game->man.x = bx + bw;
				mx = bx + bw;
			
			}
			else if( ((mx+bw) > bx) && (mx < bx) ){
				// rubbing against right edge
				game->man.x = bx - mw;
				mx = mx - mw;
			}
		}

		if ( ((mx+mw) > bx) && (mx<(bx+bw)) ) {
			//are we bumping our head?
			if ( (my<(by+bh)) && my>by) {
				game->man.y = by + bh;
				game->man.dy = 0;//bumped our head, stop any jump velocity
				game->man.onLedge = 1;
			}
			else if( ((my+mh) > by) && (my < by)){
				game->man.y = by - mh;
				game->man.dy = 0;//landed on this ledge, stop any jump velocity
				game->man.onLedge = 1;
			}
			
		}
	}
}


int processEvents(SDL_Window* window, GameState* game) {

	SDL_Event event;
	int done = 0;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_WINDOWEVENT_CLOSE: {
			if (window) {
				SDL_DestroyWindow(window);
				window = NULL;
				done = 1;
			}
		}
		break;

		case SDL_KEYDOWN: {
			switch (event.key.keysym.sym)
			{
				case SDLK_ESCAPE:
					done = 1;
				break;

				case SDLK_UP:
					//printf("%g", game->man.dy);
					if (game->man.onLedge) {
						game->man.dy = -12;
						game->man.onLedge = 0;
					}
				break;
				//case SDLK_RIGHT: { man->x += 10; } break;
				//case SDLK_LEFT: { man->x -= 10; } break;
			}
		}
		break;

		case SDL_QUIT:
			done = 1;
			break;

		}
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_LEFT]) {
		game->man.x -= 10;
	}

	if (state[SDL_SCANCODE_RIGHT]) {
		(*game).man.x += 10;
	}

/*MAN DONT FLY ANYMORE
	if (state[SDL_SCANCODE_UP]) {
		game->man.y -= 10;
	}

	if (state[SDL_SCANCODE_DOWN]) {
		game->man.y += 10;
	}
*/
	return done;
}


void doRender(SDL_Renderer* renderer, GameState* game) {
	//render display
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	for (int i = 0; i < 100; i++) {
		SDL_Rect ledgeRect = {game->ledges[i].x, game->ledges[i].y,
			game->ledges[i].w, game->ledges[i].h };

		SDL_RenderCopy(renderer, game->brick, NULL, &ledgeRect);
	}

	//draw rectangle at man's position
	SDL_Rect rect = { (*game).man.x , game->man.y, 60, 60 };
	SDL_RenderCopyEx(renderer, game->manFrames[0], NULL, &rect, 0, NULL, 0);
	//SDL_RenderFillRect(renderer, &rect);

	/*
	for (int i = 0; i < 100; i++) {
		//draw star image
		SDL_Rect starRect = { game->stars[i].x, game->stars[i].y,68,68};
		SDL_RenderCopy(renderer, game->star, NULL, &starRect);
	}
	*/


	//here im drawing 2 things, the 1st one is the white rectangle
	//and given that is the first thing breing drawn
	//the white rectangle will be behind the star

	SDL_RenderPresent(renderer);

}


int main(int argc, char* args[]) {

	GameState gameState;


	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	


	SDL_Init(SDL_INIT_VIDEO);
	srand((int) time(NULL));

	window = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	gameState.renderer = renderer;

	loadGame(&gameState);
	
	int done = 0;

	while (!done) {

		done = processEvents(window, &gameState);
		
		process(&gameState);
		collisionDetect(&gameState);
		
		doRender(renderer, &gameState);

		//SDL_Delay(50);
	}


	SDL_DestroyTexture(gameState.star);

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	SDL_Quit();
	return 0;
}