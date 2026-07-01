#include "Game.h"

Game::Game()
	: is_running(false),
	  window(nullptr)
{
	tick_count = 0;
}

bool Game::initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow("Game Programming in C++ (Chapter 1)",
							  SDL_WINDOWPOS_CENTERED, // window pos x
							  SDL_WINDOWPOS_CENTERED, // window pos y
							  WINDOW_SIZE_X,		  // window width
							  WINDOW_SIZE_Y,		  // window height
							  0);					  // window flags

	if (!window)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!renderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	ball_pos = {WINDOW_SIZE_X / 2.0f, WINDOW_SIZE_Y / 2.0f};
	ball_velocity = {-200.0f, 235.0f};
	paddle_pos = {100.0f, WINDOW_SIZE_Y / 2.0f};

	is_running = true;
	return true;
}

void Game::run_loop()
{
	while (is_running)
	{
		process_input();
		update_game();
		render();
	}
}

void Game::shutdown()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::process_input()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			is_running = false;
			break;
		}
	}

	const Uint8 *keyboard_state = SDL_GetKeyboardState(NULL);

	if (keyboard_state[SDL_SCANCODE_ESCAPE])
	{
		is_running = false;
	}

	paddle_direction = 0;
	if (keyboard_state[SDL_SCANCODE_W])
	{
		paddle_direction -= 1;
	}
	if (keyboard_state[SDL_SCANCODE_S])
	{
		paddle_direction += 1;
	}
}

void Game::update_game()
{
	/* ###### ENGINE LOGIC ###### */

	// wait until 16ms has passed since last frame
	// it's essentially doing 'while(SDL_GetTicks() < tick_count + 16)' but with some overflow protection
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), tick_count + 16))
		;

	// calculate current dt in seconds
	float delta_time = (SDL_GetTicks() - tick_count) / 1000.0f;

	// force delta_tima cap if it should exceed some large threshold (like when debugging)
	if (delta_time > 0.05f)
	{
		delta_time = 0.05f;
	}

	// store tick count for the next frame
	tick_count = SDL_GetTicks();

	/* ###### GAME LOGIC ###### */
	ball_pos.x += ball_velocity.x * delta_time;
	ball_pos.y += ball_velocity.y * delta_time;

	// wall collision
	if ((ball_pos.y - (THICKNESS / 2) < THICKNESS && ball_velocity.y < 0) || (ball_pos.y + (THICKNESS / 2) > WINDOW_SIZE_Y - THICKNESS && ball_velocity.y > 0))
	{
		ball_velocity.y *= -1;
	}
	else if ((ball_pos.x - (THICKNESS / 2) < THICKNESS && ball_velocity.x < 0) || (ball_pos.x + (THICKNESS / 2) > WINDOW_SIZE_X - THICKNESS && ball_velocity.x > 0))
	{
		ball_velocity.x *= -1;
	}

	// ball and paddle collision
	float diff = std::abs(ball_pos.y - paddle_pos.y);

	if (diff <= PADDLE_HEIGHT / 2.0f &&
		ball_pos.x - (THICKNESS / 2) <= paddle_pos.x + (THICKNESS / 2) &&
		ball_pos.x + (THICKNESS / 2) >= paddle_pos.x &&
		ball_velocity.x < 0)
	{
		ball_velocity.x *= -1;

		// push the ball outside the paddle
		ball_pos.x = paddle_pos.x + THICKNESS;
	}

	if (paddle_direction != 0)
	{
		paddle_pos.y += paddle_direction * PADDLE_SPEED * delta_time;

		if (paddle_pos.y < (PADDLE_HEIGHT / 2) + THICKNESS)
		{
			paddle_pos.y = (PADDLE_HEIGHT / 2) + THICKNESS;
		}
		else if (paddle_pos.y > WINDOW_SIZE_Y - (PADDLE_HEIGHT / 2) - THICKNESS)
		{
			paddle_pos.y = WINDOW_SIZE_Y - (PADDLE_HEIGHT / 2) - THICKNESS;
		}
	}
}

void Game::render()
{
	// set draw color for the state machine (like immediate mode)
	SDL_SetRenderDrawColor(renderer, 100, 149, 237, 255);
	// clear the backbuffer with whatecer the current draw color is (set above)
	SDL_RenderClear(renderer);

	// walls
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_Rect wall_top{
		0,
		0,
		WINDOW_SIZE_X,
		THICKNESS};
	SDL_RenderFillRect(renderer, &wall_top);

	SDL_Rect wall_bottom{
		0,
		WINDOW_SIZE_Y - THICKNESS,
		WINDOW_SIZE_X,
		THICKNESS};
	SDL_RenderFillRect(renderer, &wall_bottom);

	SDL_Rect wall_left{
		0,
		0,
		THICKNESS,
		WINDOW_SIZE_Y};
	SDL_RenderFillRect(renderer, &wall_left);

	SDL_Rect wall_right{
		WINDOW_SIZE_X - THICKNESS,
		0,
		THICKNESS,
		WINDOW_SIZE_Y};
	SDL_RenderFillRect(renderer, &wall_right);

	// balls
	SDL_Rect ball_rect{
		static_cast<int>(ball_pos.x - THICKNESS / 2),
		static_cast<int>(ball_pos.y - THICKNESS / 2),
		THICKNESS,
		THICKNESS};

	SDL_RenderFillRect(renderer, &ball_rect);

	// paddle
	SDL_Rect paddle_rect{
		static_cast<int>(paddle_pos.x - THICKNESS / 2),
		static_cast<int>(paddle_pos.y - PADDLE_HEIGHT / 2),
		THICKNESS,
		PADDLE_HEIGHT,
	};

	SDL_RenderFillRect(renderer, &paddle_rect);

	// swap buffers (and present it to the screen)
	SDL_RenderPresent(renderer);
}