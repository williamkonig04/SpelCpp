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
    SDL_Window* window = SDL_CreateWindow("Williams Spel", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Event event;
    bool quit = false;

    SDL_Texture* texture = NULL;
    SDL_Texture* backgroundTextureRoom0 = NULL;
    SDL_Texture* backgroundTextureRoom1 = NULL;
    SDL_Texture* backgroundTextureRoom2 = NULL;
    SDL_Texture* backgroundTextureRoom3 = NULL;
    SDL_Texture* backgroundTextureRoom4 = NULL;
    SDL_Texture* backgroundTextureRoom5 = NULL;
    SDL_Texture* backgroundTextureRoom6 = NULL;
    SDL_Texture* backgroundTextureRoom7 = NULL;
    

    // Bakgrunderna ligger i SDL-Smile
    SDL_Surface* tempBackgroundRoom0 = IMG_Load("roomStart.png");
    SDL_Surface* tempBackgroundRoom1 = IMG_Load("room1.png");
    SDL_Surface* tempBackgroundRoom2 = IMG_Load("room2.png");
    SDL_Surface* tempBackgroundRoom3 = IMG_Load("room3.png");
    SDL_Surface* tempBackgroundRoom4 = IMG_Load("room4.png");
    SDL_Surface* tempBackgroundRoom5 = IMG_Load("room5.png");
    SDL_Surface* tempBackgroundRoom6 = IMG_Load("room6.png");
    SDL_Surface* tempBackgroundRoom7 = IMG_Load("bossRoom.png");
    
    
    SDL_Surface* temp = IMG_Load("william.png");
    SDL_Texture* hud = NULL;
    SDL_Surface* tempHud = IMG_Load("heart.png");

    //Nyckel karta
    SDL_Texture* keyTexture = NULL;
    SDL_Surface* surfaceTemp = IMG_Load("key.png");
    keyTexture = SDL_CreateTextureFromSurface(renderer, surfaceTemp);
    SDL_Rect rectNyckel;
    rectNyckel.x = 500;
    rectNyckel.y = 300;
    rectNyckel.w = 50;
    rectNyckel.h = 50;

    //Brev Bild
    SDL_Texture* brevTexture = NULL;
    SDL_Surface* brevSurfaceTemp = IMG_Load("brev.png");
    brevTexture = SDL_CreateTextureFromSurface(renderer, brevSurfaceTemp);
    SDL_Rect rectBrev;
    rectBrev.x = 500;
    rectBrev.y = 100;
    rectBrev.w = 50;
    rectBrev.h = 50;

    //Brev Text
    SDL_Texture* brevTextTexture = NULL;
    SDL_Surface* brevTextSurfaceTemp = IMG_Load("brevText.png");
    brevTextTexture = SDL_CreateTextureFromSurface(renderer, brevTextSurfaceTemp);
    SDL_Rect rectBrevText;
    rectBrevText.x = 500;
    rectBrevText.y = 100;
    rectBrevText.w = 200;
    rectBrevText.h = 200;

    // Nyckel HUD
    SDL_Rect rectNyckelInv;
    rectNyckelInv.x = 600;
    rectNyckelInv.y = 20;
    rectNyckelInv.w = 30;
    rectNyckelInv.h = 30;


    //Filling texture with the image using a surface
    texture = SDL_CreateTextureFromSurface(renderer, temp);
    backgroundTextureRoom0 = SDL_CreateTextureFromSurface(renderer, tempBackgroundRoom0);
    backgroundTextureRoom1 = SDL_CreateTextureFromSurface(renderer, tempBackgroundRoom1);
    backgroundTextureRoom2 = SDL_CreateTextureFromSurface(renderer, tempBackgroundRoom2);
    backgroundTextureRoom3 = SDL_CreateTextureFromSurface(renderer, tempBackgroundRoom3);
    backgroundTextureRoom4 = SDL_CreateTextureFromSurface(renderer, tempBackgroundRoom4);
    backgroundTextureRoom5 = SDL_CreateTextureFromSurface(renderer, tempBackgroundRoom5);
    backgroundTextureRoom6 = SDL_CreateTextureFromSurface(renderer, tempBackgroundRoom6);
    backgroundTextureRoom7 = SDL_CreateTextureFromSurface(renderer, tempBackgroundRoom7);
    hud = SDL_CreateTextureFromSurface(renderer, tempHud);
    //Deleting the temporary surface
    SDL_FreeSurface(temp);
    SDL_FreeSurface(tempBackgroundRoom0);
    SDL_FreeSurface(tempBackgroundRoom1);
    SDL_FreeSurface(tempBackgroundRoom2);
    SDL_FreeSurface(tempBackgroundRoom3);
    SDL_FreeSurface(tempBackgroundRoom4);
    SDL_FreeSurface(tempBackgroundRoom5);
    SDL_FreeSurface(tempBackgroundRoom6);
    SDL_FreeSurface(tempBackgroundRoom7);
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
    rectBackground.w = 800; //800 pixels width
    rectBackground.h = 600; //600 pixels height

    int smileX = playerRect.x;
    int smileY = playerRect.y;
    int hastX = 0;
    int hastY = 0;
    int roomNr = 0; // Start game in start room
    bool moved = false;
    bool showKey = false;

    // Brev
    bool showBrev = true;
    bool lookingAtBrev = false;
    bool haveReadBrev = false;

    // Nycklar
    bool nycklar[3];

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
                        std::cout << "X= " << smileX << "  Y= " << smileY << std::endl;
                    }
                    break;
                case SDLK_RIGHT:
                    if (hastX > 0)
                    {
                        hastX = 0;
                        moved = false;
                        std::cout << "X= " << smileX << "  Y= " << smileY << std::endl;
                    }
                    break;
                case SDLK_UP:
                    if (hastY < 0)
                        hastY = 0;
                    std::cout << "X= " << smileX << "  Y= " << smileY << std::endl;
                    break;
                case SDLK_DOWN:
                    if (hastY > 0)
                        hastY = 0;
                    std::cout << "X= " << smileX << "  Y= " << smileY << std::endl;
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

        //Från start till rum 2
        if (hastX == 1 && smileX == 700 && roomNr == 0 && (smileY >= 250 || smileY <= 350))
        {
            if (!moved)
            {
                moved = true;
                roomNr = 2;
                smileX = 0;
                std::cout << "Går till rum 2 från start";
            }
        }
        //Från start till rum 1
        else if (hastY == -1 && smileY == 0 && roomNr == 0 && (smileX >= 250 || smileX <= 350))
        {
            if (!moved)
            {
                moved = true;
                roomNr = 1;
                smileY = 500;
                std::cout << "Går från start till rum 1";
            }
        }
        //Från rum 1 till start
        else if (hastY == 1 && smileY == 500 && roomNr == 1 && (smileX >= 250 || smileX <= 350))
        {
            if (!moved)
            {
                moved = true;
                roomNr = 0;
                smileY = 0;
                std::cout << "Går från rum 1 till start";
            }
        }
        // Från rum 1 till boss room
        else if (hastY == -1 && smileY == 0 && roomNr == 1 && (smileX >= 250 || smileX <= 350))
        {
            if (!moved)
            {
                
                if (nycklar[2] == true)
                {
                    moved = true;
                    roomNr = 7;
                    smileY = 0;
                    std::cout << "Går från rum 1 till boss room";
                }
                else
                {
                    std::cout << "Du behöver nyckel till bossen.";
                }
            }
        }
        // Från boss room till room 1
        else if (hastY == 1 && smileY == 500 && roomNr == 7 && (smileX >= 300 || smileX <= 400))
        {
            if (!moved)
            {
                moved = true;
                roomNr = 1;
                smileY = 0;
                std::cout << "Går från boss room till rum 1";
            }
        }
        // Från start till rum 3
        else if (hastY == 1 && smileY == 500 && roomNr == 0 && (smileX >= 250 || smileX <= 350))
        {
            if (!moved)
            {
                moved = true;
                roomNr = 3;
                smileY = 0;
                std::cout << "Går från start till rum 3";
            }
        }
        // Från rum 3 till start
        else if (hastY == -1 && smileY == 0 && roomNr == 3 && (smileX >= 200 || smileX <= 400))
        {
            if (!moved)
            {
                moved = true;
                roomNr = 0;
                smileY = 500;
                
                std::cout << "Går från rum 3 till start";
            }
        }

        //Från start till rum 4
        else if (hastX == -1 && smileX == 0 && roomNr == 0 && (smileY >= 250 || smileY <= 350))
        {
            if (!moved)
            {
                moved = true;
                roomNr = 4;
                smileX = 700;
                std::cout << "Går till rum 4 från start";
            }
        }
        //Från rum 4 till start
        else if (hastX == 1 && smileX == 700 && roomNr == 4 && (smileY >= 250 || smileY <= 350))
        {
            if (!moved)
            {
                moved = true;
                roomNr = 0;
                smileX = 0;
                std::cout << "Går till start från rum 4";
            }
        }
        // Från rum 2 till start
        else if (hastX == -1 && smileX == 0 && roomNr == 2 && (smileY >= 210 || smileY <= 350))
        {
            if (!moved)
            {
                moved = true;
                roomNr = 0;
                smileX = 700;
                std::cout << "Går från rum 2 till start";
            }
        }

        // Från rum 2 till rum 6
        else if (hastY == 1 && smileY == 500 && roomNr == 2 && (smileX >= 300 || smileX <= 400))
        {
        if (!moved)
        {
            moved = true;
            roomNr = 6;
            smileX = 700;
            smileY = 250;
            std::cout << "Går från rum 2 till rum 6";
        }
        }

        // Från rum 3 till rum 6
        else if (hastY == -1 && smileY == 500 && roomNr == 3 && (smileY >= 300 || smileY <= 400))
        {
            if (!moved)
            {
                moved = true;
                roomNr = 6;
                smileX = 350;
                smileY = 500;
                std::cout << "Går från rum 3 till rum 6";
            }
        }
        // Från rum 5 till rum 3
        else if (hastX == 1 && smileX == 700 && roomNr == 5 && (smileY >= 210 || smileY <= 300))
        {
        if (!moved)
        {
            moved = true;
            roomNr = 3;
            smileX = 0;
            std::cout << "Går från rum 5 till rum 3";
        }
        }

        // Från rum 3 till rum 6
        else if (hastY == 1 && smileY == 500 && roomNr == 3 && (smileY >= 300 || smileY <= 400))
        {
        if (!moved)
        {
            moved = true;
            roomNr = 6;
            smileY = 0;
            std::cout << "Går från rum 3 till rum 6";
        }
        }

        // Från rum 6 till rum 3
        else if (hastY == -1 && smileY == 0 && roomNr == 6 && (smileX >= 300 || smileX <= 400))
        {
        if (!moved)
        {
            moved = true;
            roomNr = 3;
            smileY = 500;
            std::cout << "Går från rum 6 till rum 3";
        }
        }

        // Från rum 6 till rum 2
        else if (hastX == 1 && smileX == 700 && roomNr == 6 && (smileY >= 200 || smileY <= 300))
        {
        if (!moved)
        {
            moved = true;
            roomNr = 2;
            smileY = 500;
            smileX = 350;
            std::cout << "Går från rum 6 till rum 2";
        }
        }

        //Copying the texture on to the window using renderer and rectangle
        // Renderar det rum man är i
        if (roomNr == 0) {
            SDL_RenderCopy(renderer, backgroundTextureRoom0, NULL, &rectBackground);
            
        }
        if (showBrev == true)
        {
            SDL_RenderCopy(renderer, brevTexture, NULL, &rectBrev);
        }

        else if (roomNr == 1) {
            SDL_RenderCopy(renderer, backgroundTextureRoom1, NULL, &rectBackground);
        }
        else if (roomNr == 2)
        {
            SDL_RenderCopy(renderer, backgroundTextureRoom2, NULL, &rectBackground);
        }
        else if (roomNr == 3)
        {
            SDL_RenderCopy(renderer, backgroundTextureRoom3, NULL, &rectBackground);
        }
        else if (roomNr == 4)
        {
            SDL_RenderCopy(renderer, backgroundTextureRoom4, NULL, &rectBackground);
        }
        else if (roomNr == 5)
        {
            SDL_RenderCopy(renderer, backgroundTextureRoom5, NULL, &rectBackground);
        }
        else if (roomNr == 6)
        {
            SDL_RenderCopy(renderer, backgroundTextureRoom6, NULL, &rectBackground);
        }
        else if (roomNr == 7)
        {
            SDL_RenderCopy(renderer, backgroundTextureRoom7, NULL, &rectBackground);
        }

        if (roomNr == 1 && intersection(playerRect, rectNyckel)) // Plockar upp nyckeln
        {
            showKey = true;
        }
        if (roomNr == 0 && intersection(playerRect, rectBrev) && showBrev == true) // Läser brev
        {
            std::cout << "PÅ BREV" << std::endl;
            haveReadBrev = true;
            lookingAtBrev = true;
            SDL_RenderCopy(renderer, brevTextTexture, NULL, &rectBrev);
        }
        if (showKey) // Visar Nyckel i HUD
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
        if (haveReadBrev == true && intersection(playerRect, rectBrev) == false)
        {
            showBrev = false;
            lookingAtBrev = false;
            rectBrev.w = 50;
            rectBrev.h = 50;
            rectBrev.x = 500;
            rectBrev.y = 100;
        }
        if (lookingAtBrev == true)
        {
            showBrev = true;
            rectBrev.w = 500;
            rectBrev.h = 500;
            rectBrev.x = 100;
            rectBrev.y = 100;
        }
    }

    //Deleting the texture
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(backgroundTextureRoom0);
    SDL_DestroyTexture(backgroundTextureRoom1);
    SDL_DestroyTexture(backgroundTextureRoom2);
    SDL_DestroyTexture(backgroundTextureRoom3);
    SDL_DestroyTexture(backgroundTextureRoom4);
    SDL_DestroyTexture(backgroundTextureRoom5);
    SDL_DestroyTexture(backgroundTextureRoom6);
    SDL_DestroyTexture(backgroundTextureRoom7);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    //For quitting IMG systems
    IMG_Quit();

    SDL_Quit();

    return 0;
}