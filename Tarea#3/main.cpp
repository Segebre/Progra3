#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#include<map>
#include<vector>
#include <stdlib.h>
#include<SDL2/SDL_mixer.h>

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event Event;
SDL_Texture *background,*character,*character2, *star, *tiros[5];
SDL_Rect rect_background,rect_character,rect_character2, rect_star, rect_tiros[5];

//Funcion para collision
bool collision(SDL_Rect r1, SDL_Rect r2)
{
    if(r1.x + r1.w < r2.x)
        return false;
    if(r1.x > r2.x + r2.w)
        return false;
    if(r1.y + r1.h < r2.y)
        return false;
    if(r1.y > r2.y + r2.h)
        return false;
    return true;
}

int main( int argc, char* args[] )
{
    //Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 10;
    }
    //Creates a SDL Window
    if((window = SDL_CreateWindow("Ahmed es otro rollo!", 100, 100, 500/*WIDTH*/, 250/*HEIGHT*/, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
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

    //Personaje 1
    character = IMG_LoadTexture(renderer, "personaje/down1.png");
    SDL_QueryTexture(character, NULL, NULL, &w, &h);
    rect_character.x = 0; rect_character.y = 100; rect_character.w = w; rect_character.h = h;

    //Personaje 2
    character2 = IMG_LoadTexture(renderer, "personaje/down12.png");
    SDL_QueryTexture(character2, NULL, NULL, &w, &h);
    rect_character2.x = 450; rect_character2.y = 150; rect_character2.w = w; rect_character2.h = h;

    //star
    star = IMG_LoadTexture(renderer, "personaje/star.png");
    SDL_QueryTexture(star, NULL, NULL, &w, &h);
    rect_star.x = rand() % 468; rect_star.y = rand() % 217; rect_star.w = w; rect_star.h = h;

    //tiros
    tiros[0] = IMG_LoadTexture(renderer, "personaje/shotd1.png");
    SDL_QueryTexture(tiros[0], NULL, NULL, &w, &h);
    //rect_tiros.x = rand() % 468; rect_star.y = rand() % 217; rect_star.w = w; rect_star.h = h;

    //Personaje 1
    char orientation = 'd';// d u l r
    int current_sprite = 0;
    int animation_velocity = 20;
    int velocity = 1;
    int frame = 0;
    map<char,vector<SDL_Texture*> >sprites;
    sprites['u'].push_back(IMG_LoadTexture(renderer, "personaje/up1.png"));
    sprites['u'].push_back(IMG_LoadTexture(renderer, "personaje/up2.png"));
    sprites['d'].push_back(IMG_LoadTexture(renderer, "personaje/down1.png"));
    sprites['d'].push_back(IMG_LoadTexture(renderer, "personaje/down2.png"));
    sprites['l'].push_back(IMG_LoadTexture(renderer, "personaje/left1.png"));
    sprites['l'].push_back(IMG_LoadTexture(renderer, "personaje/left2.png"));
    sprites['r'].push_back(IMG_LoadTexture(renderer, "personaje/right1.png"));
    sprites['r'].push_back(IMG_LoadTexture(renderer, "personaje/right2.png"));

    //Personaje 2
    char orientation2 = 'd';// d u l r
    int current_sprite2 = 0;
    //int animation_velocity2 = 20;
    //int velocity2 = 3;
    map<char,vector<SDL_Texture*> >sprites2;
    sprites2['u'].push_back(IMG_LoadTexture(renderer, "personaje/up12.png"));
    sprites2['u'].push_back(IMG_LoadTexture(renderer, "personaje/up22.png"));
    sprites2['d'].push_back(IMG_LoadTexture(renderer, "personaje/down12.png"));
    sprites2['d'].push_back(IMG_LoadTexture(renderer, "personaje/down22.png"));
    sprites2['l'].push_back(IMG_LoadTexture(renderer, "personaje/left12.png"));
    sprites2['l'].push_back(IMG_LoadTexture(renderer, "personaje/left22.png"));
    sprites2['r'].push_back(IMG_LoadTexture(renderer, "personaje/right12.png"));
    sprites2['r'].push_back(IMG_LoadTexture(renderer, "personaje/right22.png"));


    //Aqui esta todo el sonido
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2,2048);

    Mix_Music *musica= Mix_LoadMUS("Kalimba.mp3");
    Mix_Chunk *sonido= Mix_LoadWAV("sound.wav");

    //Main Loop
    while(true)
    {
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                return 0;
            }
        }

        const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

        //musica 8acostado
        if(!Mix_PlayingMusic())
            Mix_PlayMusic(musica,1);

        //Personaje 1
        if(currentKeyStates[ SDL_SCANCODE_D ] && rect_character.x < 468)
        {
            rect_character.x+=velocity;
            if(collision(rect_character,rect_character2))
                rect_character.x-=velocity;
            orientation='r';
        }
        if(currentKeyStates[ SDL_SCANCODE_A ] && rect_character.x >= 0)
        {
            rect_character.x-=velocity;
            if(collision(rect_character,rect_character2))
                rect_character.x+=velocity;
            orientation='l';
        }
        if(currentKeyStates[ SDL_SCANCODE_S ] && rect_character.y < 217)
        {
            rect_character.y+=velocity;
            if(collision(rect_character,rect_character2))
                rect_character.y-=velocity;
            orientation='d';
        }
        if(currentKeyStates[ SDL_SCANCODE_W ] && rect_character.y > 3)
        {
            rect_character.y-=velocity;
            if(collision(rect_character,rect_character2))
                rect_character.y+=velocity;
            orientation='u';
        }
        if(currentKeyStates[ SDL_SCANCODE_SPACE ])
        {

        }

        if(frame%animation_velocity==0)
        {
            current_sprite++;
            if(current_sprite>1)
                current_sprite=0;
        }

        //Personaje 2
        if(currentKeyStates[ SDL_SCANCODE_RIGHT ] && rect_character2.x < 468)
        {
            rect_character2.x+=velocity;
            if(collision(rect_character2,rect_character))
                rect_character2.x-=velocity;
            orientation2='r';
        }
        if(currentKeyStates[ SDL_SCANCODE_LEFT ] && rect_character2.x >= 0)
        {
            rect_character2.x-=velocity;
            if(collision(rect_character2,rect_character))
                rect_character2.x+=velocity;
            orientation2='l';
        }
        if(currentKeyStates[ SDL_SCANCODE_DOWN ] && rect_character2.y < 217)
        {
            rect_character2.y+=velocity;
            if(collision(rect_character2,rect_character))
                rect_character2.y-=velocity;
            orientation2='d';
        }
        if(currentKeyStates[ SDL_SCANCODE_UP ] && rect_character2.y > 3)
        {
            rect_character2.y-=velocity;
            if(collision(rect_character2,rect_character))
                rect_character2.y+=velocity;
            orientation2='u';
        }
//        if(currentKeyStates[ SDL_SCANCODE_LSHIFT ])
//        {
//            velocity=6;
//            animation_velocity=10;
//        }else
//        {
//            velocity=3;
//            animation_velocity=20;
//        }
//

        //Aqui la estrella cambia de posicion si la tocan
        if(collision(rect_character,rect_star))
        {
            Mix_PlayChannel(-1,sonido,0);
            rect_star.x = rand() % 468;
            rect_star.y = rand() % 217;
            cout<<"Player 1"<<endl;
        }
        else if(collision(rect_character2,rect_star))
        {
            Mix_PlayChannel(-1,sonido,0);
            rect_star.x = rand() % 468;
            rect_star.y = rand() % 217;
            cout<<"Player 2"<<endl;
        }
        if(frame%animation_velocity==0)
        {
            current_sprite2++;
            if(current_sprite2>1)
                current_sprite2=0;
        }

        SDL_Delay(17);

        //cout<<frame<<endl;

        if(currentKeyStates[ SDL_SCANCODE_P ])
        {
            cout<<rect_character.x<<endl;
            cout<<rect_character.y<<endl;
        }

        SDL_RenderCopy(renderer, background, NULL, &rect_background);
        SDL_RenderCopy(renderer, sprites[orientation][current_sprite], NULL, &rect_character);
        SDL_RenderCopy(renderer, sprites2[orientation2][current_sprite2], NULL, &rect_character2);
        SDL_RenderCopy(renderer, star, NULL, &rect_star);
        SDL_RenderPresent(renderer);
        frame++;
    }

	return 0;
}
