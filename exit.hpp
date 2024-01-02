#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>



void exitGame(SDL_Renderer* renderer,SDL_Window* window,SDL_Surface* youLoseSurface,SDL_Texture* youLoseTexture,
                SDL_Surface* youWinSurface,SDL_Texture* youWinTexture,SDL_Surface* menuSurface,
                SDL_Texture* menuTexture,SDL_Surface* helpSurface,SDL_Texture* helpTexture,
                SDL_Surface* makeConnectionSurface,SDL_Texture * makeConnectionTexture,
                SDL_Surface* creditSurface,SDL_Texture *creditTexture

){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = NULL;
    window = NULL;
    SDL_FreeSurface(youLoseSurface);
    SDL_DestroyTexture(youLoseTexture);
    SDL_FreeSurface(youWinSurface);
    SDL_DestroyTexture(youWinTexture);
    SDL_FreeSurface(menuSurface);
    SDL_DestroyTexture(menuTexture);
    SDL_FreeSurface(helpSurface);
    SDL_DestroyTexture(helpTexture);
    SDL_FreeSurface(makeConnectionSurface);
    SDL_DestroyTexture(makeConnectionTexture);
    SDL_FreeSurface(creditSurface);
    SDL_DestroyTexture(creditTexture);
    youWinSurface = NULL;
    youWinTexture =NULL;
    youLoseSurface=NULL;
    youLoseTexture = NULL;
    menuSurface = NULL;
    menuTexture = NULL;
    helpSurface = NULL;
    helpTexture = NULL;
    makeConnectionSurface = NULL;
    makeConnectionTexture = NULL;
    creditSurface = NULL;
    creditTexture = NULL;
    IMG_Quit();
    SDL_Quit();
}