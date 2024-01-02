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
#include"gameloop.hpp"
#include"exit.hpp"

using namespace std;

int main(){

    //player
    pair<int,int> playerPos = {TILE_SIZE,TILE_SIZE};
    pair<int,int> playerCood = {playerPos.first/TILE_SIZE,playerPos.second/TILE_SIZE}; 
    pair<int,int> oldDir = {0,0};
    pair<int,int> playerDir={0,0};
    int playerSpeed=3;
    //enemy
    pair<int,int> enemyCood = {ENEMY_X,ENEMY_Y};
    pair<int,int> enemyPos = {enemyCood.first * TILE_SIZE,enemyCood.second* TILE_SIZE};
    pair<int,int> oldEnemyDir = {0,0};
    pair<int,int> enemyDir = {0,0};
    int enemySpeed=3;
    //WINning
    pair<int,int> winningPosCood={38,18};
    pair<int,int> winningPos = {winningPosCood.first*TILE_SIZE,winningPosCood.second*TILE_SIZE};
    bool playerWinner = false;
    bool enemyWinner = false;



    //initialise
    SDL_Window* window = SDL_CreateWindow("NIT HAMIRPUR  MAZE GAME",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);

    //sounds

    // Mix_Chunk* introSound = NULL;
    // Mix_Chunk* introSound2 = NULL;
    // Mix_Chunk* deathSound = NULL;
    // Mix_Chunk* winningSound = NULL;
    
    // Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048);

    // introSound = Mix_LoadWAV("res/intro.wav");
    // introSound2 = Mix_LoadWAV("res/intro2.wav");
    // deathSound = Mix_LoadWAV("res/death.wav");
    // winningSound = Mix_LoadWAV("res/winning.wav");



    //textures and surfaces
    SDL_Surface* youLoseSurface = IMG_Load("res/youlose.png");
    SDL_Texture* youLoseTexture = SDL_CreateTextureFromSurface(renderer,youLoseSurface);
    SDL_Surface* menuSurface = IMG_Load("res/menu.png");
    SDL_Texture* menuTexture = SDL_CreateTextureFromSurface(renderer,menuSurface);
    SDL_Surface* creditSurface = IMG_Load("res/credits.png");
    SDL_Texture* creditTexture = SDL_CreateTextureFromSurface(renderer,creditSurface);
    SDL_Surface* helpSurface = IMG_Load("res/help.png");
    SDL_Texture* helpTexture = SDL_CreateTextureFromSurface(renderer,helpSurface);
    SDL_Surface* makeConnectionSurface = IMG_Load("res/socket.png");
    SDL_Texture* makeConnectionTexture = SDL_CreateTextureFromSurface(renderer,makeConnectionSurface);
    SDL_Surface* youWinSurface = IMG_Load("res/youwin.png");
    SDL_Texture* youWinTexture = SDL_CreateTextureFromSurface(renderer,youWinSurface);
    bool menu=true,credits=false,help=false,exit=false,makeConnection=false,youWin=false,youLose=false;
    



    //mainloop
    bool quitGameLoop = false;
    bool player = false, enemy =false;
    int buffer[50];
    bool connected = false;
    int new_socket,client_fd;
    while(exit==false){

        int x,y;
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT){

                exit=true;
            }
            if(event.type == SDL_MOUSEBUTTONDOWN ){
                SDL_GetMouseState(&x,&y);
                break;
            }
            if(event.type==SDL_KEYDOWN && makeConnection==true){
                    if(event.key.keysym.sym == SDLK_s){
                        player=true;
                        break;
                    }
                    if(event.key.keysym.sym == SDLK_c){
                        enemy = true;
                        break;
                    }
            }
         
        }
        if(menu==true){
            SDL_RenderCopy(renderer,menuTexture,NULL,NULL);
            if(x>375 && x<840 && y>245 && y<293){
                menu = false;
                makeConnection = true;
            }
            if(x>482 && x<760 && y>330 && y<390){
                menu = false;
                help = true;
            }
            if(x>380 && x<830 && y>425 && y<470){
                menu = false;
                credits =true;
            }
            if(x>476 && x<737 && y>500 && y<553){
                menu = false;
                exit = true;
            }

        }
        if(credits==true){
            SDL_RenderCopy(renderer,creditTexture,NULL,NULL);
            if(x>454 && x<751 && y>484 && y<554){
                credits = false;
                menu = true;
            }
        }
        if(help==true){
            SDL_RenderCopy(renderer,helpTexture,NULL,NULL);
            if(x>456 && x<773 && y>512 && y<584){
                help =false;
                menu= true;
            }
        }
        if(makeConnection==true){
            
            SDL_RenderCopy(renderer,makeConnectionTexture,NULL,NULL);
            if(x>461 && x<774 && y>476 && y<536){
                makeConnection=false;
                menu = true;
            }

            
            //socket
            
            if(player){
                struct sockaddr_in serv_addr;
                //char buffer[200];
                int server_fd = socket(AF_INET, SOCK_STREAM, 0);
                serv_addr.sin_family = AF_INET;
                serv_addr.sin_port = htons(8080);
                serv_addr.sin_addr.s_addr =  inet_addr("127.0.0.1");
                socklen_t serv_len = sizeof(serv_addr);
                bind(server_fd,(struct sockaddr * )&serv_addr,serv_len);
                listen(server_fd, 3);
                new_socket = accept(server_fd,(struct sockaddr*)&serv_addr,(socklen_t*)&serv_len);
                buffer[35] = 11;
                send(new_socket,buffer,200,0);
                read(new_socket,buffer,200);
                    connected = true;
                

            }
            if(enemy){
                //char buffer[200];
                client_fd = socket(AF_INET,SOCK_STREAM,0);
                struct sockaddr_in cli_addr;
                socklen_t cli_len;
                cli_addr.sin_family = AF_INET;
                cli_addr.sin_port= htons(8080);
               // cli_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
                cli_len = sizeof(cli_addr);
                inet_pton(AF_INET, "127.0.0.1", &cli_addr.sin_addr) ;
                int x =connect(client_fd,(struct sockaddr*)&cli_addr,cli_len);
                buffer[36] = 11;
                read(client_fd,buffer,200);
                send(client_fd,buffer,200,0);
                if(buffer[35]==11){
                    connected=true;
                }
            }
            //gameLoop
            if(connected){
                pair<bool,bool> gameReturn = gameLoop(player,enemy,quitGameLoop,playerDir,playerPos,playerCood,oldDir,playerSpeed,enemySpeed,enemyCood,enemyPos,
                oldEnemyDir,winningPos,playerWinner,enemyWinner,enemyDir,renderer,buffer,new_socket,client_fd,exit);
                makeConnection = false;
                connected = false;
                player = false;
                enemy=false;
                buffer[35]=0;

               
                if(gameReturn.second == true){
                    exit=true;
                }else{
                    if(gameReturn.first==true){
                        youWin=true;
                    }else{
                        youLose=true;
                    }
                }
            }
            
            //gameLoop
            
        }
        
        if(youWin==true){
            SDL_RenderCopy(renderer,youWinTexture,NULL,NULL);
            if(x>455 && x<773 && y>453 && y<515){
                youWin=false ;
                menu=true;
            }
        }
        if(youLose==true){
            SDL_RenderCopy(renderer,youLoseTexture,NULL,NULL);
            if(x>453 && x<770 && y>453 && y<514){
                youLose=false;
                menu=true;
            }
        }
        SDL_RenderPresent(renderer);
        x=0,y=0;

        
        
        SDL_Delay(30);
    }

  




    

  




    //quit
    


    exitGame(renderer,window,youLoseSurface,youLoseTexture,youWinSurface,youWinTexture,menuSurface,menuTexture,
    helpSurface,helpTexture,makeConnectionSurface,makeConnectionTexture,creditSurface,creditTexture);
    


}