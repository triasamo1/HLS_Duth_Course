#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "ac_int.h"
#include <algorithm>
#include "mc_scverify.h"

static const short N = 6;
ac_int<N,false> Adj_G[N] = {0};

/////////////////////////////////////////////////////
//#pragma hls_design top
//int CCS_BLOCK(graph_color_old)(ac_int<N,false> Adj_G[N],int label[N]){
//    for (int i=0;i<N;i++){
//        int c = 1;
//        for (int j= 0; j<N; j++){
//            if( Adj_G[i][5-j] == 1 && label[j] == c){ //if you are connected to this node and has same color
//                c += 1;   // pick next color
//            }
//        }
//        label[i] = c;
//    }
//    return label;
//}
#pragma hls_design top
void CCS_BLOCK(graph_color_old)(ac_int<N,false> Adj_G[N],short label[N]){
    for (int i=0;i<N;i++){
        int c = 1;
        ac_int<N,false> Adj_temp = Adj_G[i];   // store it locally so you access it once every N cycles
        for (int j= 0; j<N; j++){
            if( Adj_temp[5-j] == 1 && label[j] == c){ //if you are connected to this node and has same color
                c += 1;   // pick next color
            }
        }
        label[i] = c;
    }
}

/////////////////////////////////////////////////////

CCS_MAIN(int argc, char* argv[]) {
    srand(time(NULL));
    std::cout << "Create  N-nodes graph G" << std::endl;

    std::cout << "Create Adj_G graph" << std::endl;
    Adj_G[0] = 19;
    Adj_G[1] = 41;
    Adj_G[2] = 20;
    Adj_G[3] = 10;
    Adj_G[4] = 37;
    Adj_G[5] = 50;
    for (int i=0;i<N;i++) {
        for (int j = 0; j < N; j++) {
            std::cout << Adj_G[i][5 - j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Example Graph" << std::endl;
    short graph_col[N] = {0};
    graph_color_old(Adj_G, graph_col);
    for (int i = 0; i < N; i++) {
        std::cout << "Node : " << i+1 << " with color: "<<graph_col[i] << std::endl;
    }
    std::cout << "Chromatic Number: " << *std::max_element(graph_col,graph_col+N) << std::endl;
    std::cout << "-----------------------------------------" << std::endl;

    for (int k = 0; k < 10; k++){
        ac_int<N,false> Adj[N] = {0};
        std::cout << "Generate random graph" << std::endl;
        //Generate his Adj Matrix
        for (int p =0;p<N;p++){
            Adj[p] = 0;
        }
        for (int i = 0; i < N-2; i++) {
            for (int j = N-2-i; j >= 0; j--) {
                int yes_no = rand() % 2;
                if(yes_no){
                    Adj[i][j] = 1;
                    Adj[(N - 1) - j][(N - 1) - i] = 1;
                }
            }
        }
        //------------------------
        for (int i=0;i<N;i++) {
            for (int j = 0; j < N; j++) {
                std::cout << Adj[i][5 - j] << " ";
            }
            std::cout << std::endl;
        }
        short graph_col2[N] = {0};
        graph_color_old(Adj, graph_col2);
        std::cout << "Chromatic Number: " << *std::max_element(graph_col2,graph_col2+N) << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
    }

    CCS_RETURN(0);
}
