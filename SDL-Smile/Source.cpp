#include <SDL.h>

//In order to access SDL_image features, we must include SDL_image.h
#include <SDL_image.h>
#include <iostream>
#undef main
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

typedef struct rec
{
    int xMin, xMax;
    int yMin, yMax;
} rec;
bool intersection(SDL_Rect& r1, SDL_Rect& r2)
{
    rec a;
    a.xMin = r1.x;
    a.xMax = r1.x + r1.w;
    a.yMin = r1.y;
    a.yMax = r1.y + r1.h;
    rec b;
    b.xMin = r2.x;
    b.xMax = r2.x + r2.w;
    b.yMin = r2.y;
    b.yMax = r2.y + r2.h;
    return ((a.xMin <= b.xMax && a.xMax >= b.xMin) &&
        (a.yMin <= b.yMax && a.yMax >= b.yMin));
}

int main(int argc, char** args)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    //For loading PNG images
    IMG_Init(IMG_INIT_PNG);
    SDL_Window* window = SDL_CreateWindow("Jerrys smile", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Event event;
    bool quit = false;

    SDL_Texture* texture = NULL;
    SDL_Texture* backgroundTextureRoom1 = NULL;
    SDL_Texture* backgroundTextureRoom2 = NULL;
    SDL_Texture* backgroundTextureRoom3 = NULL;
    SDL_Texture* backgroundTextureRoom4 = NULL;
    SDL_Texture* backgroundTextureRoom5 = NULL;
    SDL_Texture* backgroundTextureRoom6 = NULL;
    SDL_Texture* backgroundTextureRoom7 = NULL;
    SDL_Surface* tempBackgroundRoom1 = IMG_Load("rum1.png");
    SDL_Surface* tempBackgroundRoom2 = IMG_Load("rum2.png");
    SDL_Surface* tempBackgroundRoom3 = IMG_Load("rum3.png");
    SDL_Surface* tempBackgroundRoom4 = IMG_Load("rum4.png");
    SDL_Surface* tempBackgroundRoom5 = IMG_Load("rum5.png");
    SDL_Surface* tempBackgroundRoom6 = IMG_Load("rum6.png");
    SDL_Surface* tempBackgroundRoom7 = IMG_Load("rum7.png");
    
    SDL_Surface* temp = IMG_Load("face.png");
    SDL_Texture* hud = NULL;
    SDL_Surface* tempHud = IMG_Load("heart.png");

    //nyckel
    SDL_Texture* keyTexture = NULL;
    SDL_Surface* surfaceTemp = IMG_Load("key.png");
    keyTexture = SDL_CreateTextureFromSurface(renderer, surfaceTemp);
    SDL_Rect rectNyckel;
    rectNyckel.x = 500;
    rectNyckel.y = 300;
    rectNyckel.w = 50;
    rectNyckel.h = 50;

    SDL_Rect rectNyckelInv;
    rectNyckelInv.x = 600;
    rectNyckelInv.y = 20;
    rectNyckelInv.w = 30;
    rectNyckelInv.h = 30;


    //Filling texture with the image using a surface
    texture = SDL_CreateTextureFromSurface(renderer, temp);
    backgroundTextureRoom1 = SDL_CreateTextureFromSurface(renderer, tempBackgroundRoom1);
    backgroundTextureRoom2 = SDL_CreateTextureFromSurface(renderer, tempBackgroundRoom2);
    hud = SDL_CreateTextureFromSurface(renderer, tempHud);
    //Deleting the temporary surface
    SDL_FreeSurface(temp);
    SDL_FreeSurface(tempBackgroundRoom1);
    SDL_FreeSurface(tempBackgroundRoom2);
    SDL_FreeSurface(tempHud);
    SDL_Rect rectHud;
    rectHud.x = 20;
    rectHud.y = 20;
    rectHud.h = 50;
    rectHud.w = 50;
    SDL_Rect playerRect;

    playerRect.w = 100;
    playerRect.h = 100;
    playerRect.x = (SCREEN_WIDTH - playerRect.w) / 2;
    playerRect.y = (SCREEN_HEIGHT - playerRect.h) / 2;

    SDL_Rect rectBackground;
    rectBackground.x = 0; //Extreme left of the window
    rectBackground.y = 0; //Very bottom of the window
    rectBackground.w = 800; //100 pixels width
    rectBackground.h = 600; //100 pixels height

    int smileX = playerRect.x;
    int smileY = playerRect.y;
    int hastX = 0;
    int hastY = 0;
    int roomNr = 1;
    bool moved = false;
    bool showKey = false;
    while (!quit)
    {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_LEFT:

                    hastX = -1;
                    break;
                case SDLK_RIGHT:

                    hastX = 1;
                    break;
                case SDLK_UP:
                    hastY = -1;
                    break;
                case SDLK_DOWN:
                    hastY = 1;
                    break;
                default:
                    break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                case SDLK_LEFT:
                    if (hastX < 0)
                    {
                        hastX = 0;
                        moved = false;
                    }
                    break;
                case SDLK_RIGHT:
                    if (hastX > 0)
                    {
                        hastX = 0;
                        moved = false;
                    }
                    break;
                case SDLK_UP:
                    if (hastY < 0)
                        hastY = 0;
                    break;
                case SDLK_DOWN:
                    if (hastY > 0)
                        hastY = 0;
                    break;
                default:
                    break;
                }
                break;
            case SDL_QUIT:
                quit = true;
            default:
                break;
            }
        }


        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_Delay(5);
        if (smileX + playerRect.w + hastX <= SCREEN_WIDTH && smileX + hastX >= 0)
            smileX += hastX;
        if (smileY + playerRect.h + hastY <= SCREEN_HEIGHT && smileY + hastY >= 0)
            smileY += hastY;
        playerRect.x = smileX;
        playerRect.y = smileY;
        if (hastX == -1 && smileX == 0 && roomNr == 1 && (smileY >= 250 || smileY <= 350))
        {
            if (!moved)
            {
                moved = true;
                roomNr = 2;
                smileX = 700;
            }
        }
        else if (hastX == 1 && smileX >= 699 && roomNr == 2 && (smileY >= 250 || smileY <= 350))
        {
            if (!moved)
            {
                moved = true;
                roomNr = 1;
                smileX = 0;
            }
        }

        //Copying the texture on to the window using renderer and rectangle
        if (roomNr == 1)
            SDL_RenderCopy(renderer, backgroundTextureRoom1, NULL, &rectBackground);
        else if (roomNr == 2)
            SDL_RenderCopy(renderer, backgroundTextureRoom2, NULL, &rectBackground);

        if (roomNr == 1 && intersection(playerRect, rectNyckel))
        {
            showKey = true;
        }
        if (showKey)
        {
            SDL_RenderCopy(renderer, keyTexture, NULL, &rectNyckelInv);
        }
        else if (roomNr == 1 && !showKey)
        {
            SDL_RenderCopy(renderer, keyTexture, NULL, &rectNyckel);
        }
        SDL_RenderCopy(renderer, texture, NULL, &playerRect);
        SDL_RenderCopy(renderer, hud, NULL, &rectHud);
        SDL_RenderPresent(renderer);
    }

    //Deleting the texture
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(backgroundTextureRoom1);
    SDL_DestroyTexture(backgroundTextureRoom2);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    //For quitting IMG systems
    IMG_Quit();

    SDL_Quit();

    return 0;
}