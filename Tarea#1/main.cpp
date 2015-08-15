
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event Event;
SDL_Texture *background,*character,*aro;
SDL_Rect rect_background,rect_character,rect_aro;



int main( int argc, char* args[] )
{
    //Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 10;
    }
    //Creates a SDL Window
    if((window = SDL_CreateWindow("Image Loading", 100, 100, 500/*WIDTH*/, 250/*HEIGHT*/, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
    {
        return 20;
    }
    //SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        return 30;
    }

    //Init textures
    int w=0,h=0;
    background = IMG_LoadTexture(renderer,"fondo.png");
    SDL_QueryTexture(background, NULL, NULL, &w, &h);
    rect_background.x = 0; rect_background.y = 0; rect_background.w = w; rect_background.h = h;

    character = IMG_LoadTexture(renderer, "personaje.png");
    SDL_QueryTexture(character, NULL, NULL, &w, &h);
    rect_character.x = 70; rect_character.y = 50; rect_character.w = w; rect_character.h = h;

    aro = IMG_LoadTexture(renderer, "Aro.png");
    SDL_QueryTexture(aro, NULL, NULL, &w, &h);
    rect_aro.x = 400; rect_aro.y = 186; rect_aro.w = w; rect_aro.h = h;

    int ganaste = 0;
    //Main Loop
    do
    {
//    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                return 0;
            }
            if(Event.type == SDL_KEYDOWN)
            {
                if(Event.key.keysym.sym == SDLK_KP_6)
                    rect_character.x++;
                else if(Event.key.keysym.sym == SDLK_KP_4)
                    rect_character.x--;
                else if(Event.key.keysym.sym == SDLK_KP_8)
                    rect_character.y--;
                else if(Event.key.keysym.sym == SDLK_KP_2)
                    rect_character.y++;
                else if(Event.key.keysym.sym == SDLK_KP_9)
                {
                    rect_character.x++;
                    rect_character.y--;
                }
                else if(Event.key.keysym.sym == SDLK_KP_3)
                {
                    rect_character.x++;
                    rect_character.y++;
                }
                else if(Event.key.keysym.sym == SDLK_KP_7)
                {
                    rect_character.x--;
                    rect_character.y--;
                }
                else if(Event.key.keysym.sym == SDLK_KP_1)
                {
                    rect_character.x--;
                    rect_character.y++;
                }
            }
            if((rect_character.x < rect_aro.x+10&&rect_character.x > rect_aro.x-10) && (rect_character.y < rect_aro.y+10&&rect_character.y > rect_aro.y-10))
                ganaste=1;
        }

        SDL_RenderCopy(renderer, background, NULL, &rect_background);
        SDL_RenderCopy(renderer, character, NULL, &rect_character);
        SDL_RenderCopy(renderer, aro, NULL, &rect_aro);
        SDL_RenderPresent(renderer);
    }
    while(ganaste == 0);
        std::cout<<"Ganaste!"<<std::endl;

	return 0;
}
