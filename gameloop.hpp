#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
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
#include"constants.hpp"
#include"maze.hpp"
#include"collide.hpp"


pair<bool,bool> gameLoop(bool player ,bool enemy ,bool quit ,pair<int,int> playerDir,pair<int,int> playerPos,
  pair<int,int> playerCood,pair<int,int> oldDir,int playerSpeed,
  int enemySpeed,pair<int,int> enemyCood,pair<int,int> enemyPos,
  pair<int,int> oldEnemyDir,pair<int,int> winningPos,bool playerWinner,bool enemyWinner,
  pair<int,int> enemyDir,SDL_Renderer* renderer,int* buffer,int new_socket,int client_fd,bool exit){
    while(!quit){
    int startTime = SDL_GetTicks();
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                quit=true;
                exit=true;
                return {false,true};
            }
            if(event.type == SDL_KEYDOWN && player){
                switch(event.key.keysym.sym){
                    case SDLK_UP:
                        playerDir = {0,-1};
                        break;
                    case SDLK_DOWN:
                        playerDir = {0,1};
                        break;
                    case SDLK_RIGHT:
                        playerDir = {1,0};
                        break;
                    case SDLK_LEFT:
                        playerDir = {-1,0};
                        break;
                    default:
                        break;
                }
            }
            if(event.type == SDL_KEYDOWN && enemy){
                switch(event.key.keysym.sym){
                    case SDLK_UP:
                        enemyDir = {0,-1};
                        break;
                    case SDLK_DOWN:
                        enemyDir = {0,1};
                        break;
                    case SDLK_RIGHT:
                        enemyDir = {1,0};
                        break;
                    case SDLK_LEFT:
                        enemyDir = {-1,0};
                        break;
                    default:
                        break;
                }
            }
        }
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);

       // SDL_Surface* grass = SDL_LoadBMP()
        SDL_SetRenderDrawColor(renderer, 2, 3, 67, 255);
        for(int i=0;i<MAZE_ROWS;i++){
            for(int j=0;j<MAZE_COLS;j++){
                if(maze[i][j]==1){
                    SDL_Rect rect = {j*TILE_SIZE,i*TILE_SIZE,TILE_SIZE,TILE_SIZE};
                    SDL_RenderFillRect(renderer,&rect);
                }
            }
        }

        //change player speed
        playerCood = {playerPos.first/TILE_SIZE,playerPos.second/TILE_SIZE}; 
        if(playerPos.first%TILE_SIZE==0 && playerPos.second%TILE_SIZE==0 ){
            if(
            playerDir.first == 1 && playerDir.second == 0 && maze[playerCood.second][playerCood.first+1]==0||
            playerDir.first == 0 && playerDir.second == 1 && maze[playerCood.second+1][playerCood.first]==0||
            playerDir.first == -1 && playerDir.second == 0 && maze[playerCood.second][playerCood.first-1]==0||
            playerDir.first == 0 && playerDir.second == -1 && maze[playerCood.second-1][playerCood.first]==0
            ){
                playerPos.first += playerSpeed * playerDir.first;
                playerPos.second += playerSpeed * playerDir.second;
                oldDir = playerDir;
            }
            
        }else{
            playerPos.first += playerSpeed * oldDir.first;
            playerPos.second += playerSpeed * oldDir.second;
        }
        playerCood = {playerPos.first/TILE_SIZE,playerPos.second/TILE_SIZE}; 
        //change enemy speed
        enemyCood = {enemyPos.first/TILE_SIZE,enemyPos.second/TILE_SIZE}; 
        if(enemyPos.first%TILE_SIZE==0 && enemyPos.second%TILE_SIZE==0 ){
            if(
            enemyDir.first == 1 && enemyDir.second == 0 && maze[enemyCood.second][enemyCood.first+1]==0||
            enemyDir.first == 0 && enemyDir.second == 1 && maze[enemyCood.second+1][enemyCood.first]==0||
            enemyDir.first == -1 && enemyDir.second == 0 && maze[enemyCood.second][enemyCood.first-1]==0||
            enemyDir.first == 0 && enemyDir.second == -1 && maze[enemyCood.second-1][enemyCood.first]==0
            ){
                enemyPos.first += enemySpeed * enemyDir.first;
                enemyPos.second += enemySpeed * enemyDir.second;
                oldEnemyDir = enemyDir;
            }
            
        }else{
            enemyPos.first += enemySpeed * oldEnemyDir.first;
            enemyPos.second += playerSpeed * oldEnemyDir.second;
        }
        enemyCood = {enemyPos.first/TILE_SIZE,enemyPos.second/TILE_SIZE}; 
        //send receive
        if(player){
            buffer[1] = playerPos.first;
            buffer[2] = playerPos.second;
            buffer[3] = playerCood.first;
            buffer[4] = playerCood.second;
            buffer[5] = oldDir.first ;
            buffer[6] = oldDir.second ;
            buffer[7] = playerDir.first;
            buffer[8] = playerDir.second;
            send(new_socket,buffer,200,0);
            read(new_socket,buffer,200);
            enemyPos.first = buffer[21];
            enemyPos.second = buffer[22];
            enemyCood.first = buffer[23];
            enemyCood.second =buffer[24] ;
            oldEnemyDir.first = buffer[25] ;
            oldEnemyDir.second = buffer[26] ;
            enemyDir.first = buffer[27];
            enemyDir.second = buffer[28];
            
        }
        if(enemy){
            buffer[21] = enemyPos.first;
            buffer[22] = enemyPos.second;
            buffer[23] = enemyCood.first;
            buffer[24] = enemyCood.second;
            buffer[25] = oldEnemyDir.first ;
            buffer[26] = oldEnemyDir.second ;
            buffer[27] = enemyDir.first;
            buffer[28] = enemyDir.second;
            send(client_fd,buffer,200,0);
            read(client_fd,buffer,200);
            playerPos.first = buffer[1];
            playerPos.second = buffer[2];
            playerCood.first = buffer[3];
            playerCood.second = buffer[4];
            oldDir.first  = buffer[5];
            oldDir.second  =  buffer[6];
            playerDir.first = buffer[7];
            playerDir.second = buffer[8];
            
        }
        if(playerPos==winningPos){
            playerWinner = true;
            
            if(player) return {true,false};
            if(enemy) return {false,false};
            quit = true;
        }
        collide meet ;
        if(meet.collision(playerPos,enemyPos)){
            enemyWinner = true;
            if(player) return {false,false};
            if(enemy) return {true,false};
            quit = true;
        }
        
        //drawplayer
        if(enemyWinner==false){
            SDL_SetRenderDrawColor(renderer,0,255,0,255);
            SDL_Rect playerrect = {playerPos.first,playerPos.second,TILE_SIZE,TILE_SIZE};                
            SDL_RenderFillRect(renderer,&playerrect);
        }
        //playerdraw
        //drawenemy
        if(playerWinner==false){
            SDL_SetRenderDrawColor(renderer,255,0,0,255);  //red
            SDL_Rect enemyrect = {enemyPos.first,enemyPos.second,TILE_SIZE,TILE_SIZE};                
            SDL_RenderFillRect(renderer,&enemyrect);
        }
        //drawenmemy
        //drawWinningRect
        SDL_SetRenderDrawColor(renderer,0,255,0,255);  //red
        SDL_Rect winningrect = {winningPos.first,winningPos.second,TILE_SIZE,TILE_SIZE};                
        SDL_RenderDrawRect(renderer,&winningrect);
        //drawwinningRect
        
        SDL_RenderPresent(renderer);
        int stopTime = SDL_GetTicks();
        if(stopTime-startTime < FRAMERATE){
            SDL_Delay(FRAMERATE - (stopTime-startTime));
        }
    }
}