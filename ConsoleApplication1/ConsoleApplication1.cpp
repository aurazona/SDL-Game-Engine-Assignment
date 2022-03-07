// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "SDL.h"
#include "stdio.h"
#include "SDL_mixer.h"

//global variables go here
SDL_Window* window = NULL; //pointer for the window
SDL_Renderer* renderer = NULL; //pointer for the renderer
SDL_Surface* screenSurf = NULL; //pointer for our screen surface
SDL_Surface* hehehaha = NULL; //pointer for our image
Mix_Music* bangerTunes = NULL; //pointer for our music

bool init()
{
    bool initSucc = true; //flag to ensure we initialised correctly

    //actually initialise SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) //if somethin don't initialise correctly
    {
        printf("SDL broke lol! SDL_Error: %s\n", SDL_GetError()); //grab that error
        initSucc = false; //no success
    }
    //initialise the mixer for some sweet tunes
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("mixer broke, no music lol! SDL_mixer Error: %s\n", Mix_GetError());
        initSucc = false;
    }
    else
    {
        //try out the window machine
        window = SDL_CreateWindow("SDL Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN); //make that window
        if (window == NULL) //if no window
        {
            printf("window machine broke! SDL_Error: %s\n", SDL_GetError()); //grab that error
            initSucc = false; //no success
        }
        else
        {
            //grab that window surface
            screenSurf = SDL_GetWindowSurface(window);
        }
    }

    return initSucc;
}

bool loadMedia()
{
    bool mediaSucc = true; //flag to ensure that media loaded right

    //let's load our image
    hehehaha = SDL_LoadBMP("hehehaha.bmp");
    if (hehehaha == NULL) //if hehehaha don't work
    {
        printf("HEHEHAHA DID NOT LOAD. PANIC. WHY? ERROR: %s\n", SDL_GetError()); //hopefully find out why
        mediaSucc = false; //no success :(
    }

    //now for our music
    bangerTunes = Mix_LoadMUS("music.wav");
    if (bangerTunes == NULL) //if the music ain't there
    {
        printf("NO MUSIC. WHY? MIXER ERROR: %s\n", Mix_GetError());
        mediaSucc = false;
    }

    return mediaSucc;
}

bool exit()
{
    //FREE MY BOY HEHEHAHA
    SDL_FreeSurface(hehehaha);
    //nooooo mooooore music!
    Mix_FreeMusic(bangerTunes);
    //nuke the renderer
    SDL_DestroyRenderer(renderer);
    //nuke the window
    SDL_DestroyWindow(window);
    //also take out the mixer
    Mix_Quit();
    //show SDL the door
    SDL_Quit();
    //the end!
    return 0;
}

int main(int argc, char* argv[])
{
    //get this program going
    if (!init())
    {
        printf("initialiser broke");
    }
    else
    {
        //bring out my boy hehehaha
        if (!loadMedia())
        {
            printf("hehehaha is dead :(");
        }
        else
        {
            //prep hehehaha
            SDL_BlitSurface(hehehaha, NULL, screenSurf, NULL);

            //make hehehaha visible
            SDL_UpdateWindowSurface(window);

            //if the game isn't blaring tunes
            if (Mix_PlayingMusic() == 0)
            {
                //fix that by playing a banger
                Mix_PlayMusic(bangerTunes, -1);
            }

            //wait a couple seconds
            SDL_Delay(10000);

            //noooo mooore music!
            if (Mix_PlayingMusic() == 1)
            {
                Mix_HaltMusic();
            }
        }
    }

    //close up shop
    exit();

    //the end (for real this time)!
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
