#include <bits/stdc++.h>
using namespace std;

class collide{
    public:
    
        bool collision(pair<int,int> player , pair<int,int> enemy){
               bool ans = false ;
               if(max(player.first ,enemy.first)- min(player.first,enemy.first) <=20 & max(player.second,enemy.second)- min(player.second,enemy.second) <=20){
                   ans = true ;
               }
               return ans ;

        }
};