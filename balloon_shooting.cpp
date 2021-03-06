/*

[19 June] : I bileave this is not an MCM. We have to perform DP TSP.

[18 June] : This may be wrong. Use MCM to solved this in DP. Will update the solution.

Question Link : 

https://www.geeksforgeeks.org/samsung-delhi-interview-experience-set-38-campus/

https://interviewbubble.com/samsung-interview-questions-asked-in-samsung-3-hour-test-set-5/

Catch: Neighboring balloon comes together after the middle one is shot

Hint : Variant of travelling salesman problem

*/

#include <iostream>
using namespace std;

int N;
int arr[20];
int dp[1<<20];

bool is_visited(int comb, int idx){
    return (comb>>idx)&1;
}

int set_visited(int comb, int idx){
    return comb|(1<<idx);
}

int tsp(int visited){

    //cout<<visited<<endl;

    if(dp[visited] != -1)
        return dp[visited];

    int max_val=INT_MIN;
    int atleast_one_visited=false;

    for(int i=0;i<N;i++){
        if( !is_visited(visited,i) ){

            atleast_one_visited = true;

            int left=i,right=i;
            bool left_ok=false, right_ok=false;

            while( --left >= 0 ){
                if( !is_visited(visited,left)){
                    left_ok=true;
                    break;
                }
            }

            while( ++right < N ){
                if( !is_visited(visited,right)){
                    right_ok=true;
                    break;
                }
            }

            if( left_ok && right_ok ){
                max_val = max( max_val, (arr[left]*arr[right]) + tsp( set_visited(visited,i) ) ); // left and right are present
            }else if( left_ok ){
                max_val = max( max_val,            arr[left] + tsp( set_visited(visited,i) ) ); // only left
            }else if( right_ok ){
                max_val = max( max_val,            arr[right] + tsp( set_visited(visited,i) ) ); // only right
            }else{
                max_val = max( max_val,            arr[i]   + tsp( set_visited(visited,i) ) ); // no left and right
            }

        }
    }

    if(!atleast_one_visited){
        return dp[visited]=0;
    }

    return dp[visited] = max_val;
}


int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for(int i=0;i<(1<<20);i++){
        dp[i] = -1;
    }

    cin>>N;

    for(int i=0;i<N;i++)
        cin>> arr[i];

    cout<< tsp(0) <<endl;
}
