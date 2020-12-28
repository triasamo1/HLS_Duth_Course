#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include "mc_scverify.h"
static const int M = 150;
static const int N = 100;

#pragma hls_design top
void CCS_BLOCK(with_queue)(short (&img)[N][M], short (&out_Q)[N][M]){
    short sum;
    short myqueue[5];
    short front = 0;  //for queue functionality
    short rear = 0;
    ROW:for (int i = 0; i < N; ++i) {
        //init new queue
        myqueue[rear] = 0;
        rear++;
        myqueue[rear] = 0;
        rear++;
        myqueue[rear] = img[i][0];
        rear++;                         //  2 mem accesses for pre-processing(1 clk)
        //init sum variable
        sum = myqueue[rear - 1];
        myqueue[rear] = img[i][1];
        rear++;
        sum += myqueue[rear - 1];
        COL:for (int j = 2; j < M; ++j) {
            //push new element in
            myqueue[rear] = img[i][j];      //  2 mem accesses for main process(1 clk)
            rear++;
            sum += myqueue[rear - 1];
            //calculate cell in center
            out_Q[i][j-2] = sum / 5;
            //decrease sum by the oldest element and pop it out
            sum -=  myqueue[front];
            //remove from queue
            myqueue[0] = myqueue[1];
            myqueue[1] = myqueue[2];
            myqueue[2] = myqueue[3];
            myqueue[3] = myqueue[4];
            myqueue[4] = 0;
            // decrement rear
            rear--;
        }
        out_Q[i][M-2] = sum / 5;          //  2 mem accesses for last two cols (1 clk)
        sum -=  myqueue[front];
        out_Q[i][M-1] = sum / 5;
        // set queue ready for next row
        rear=0;
    }
}

void original(short (&img)[N][M], short (&out_orig)[N][M] ){
    // scan the image row by row
    // N = #row, M = #col
    short p1,p2,p3,p4,p5;
    ROW:for (int i = 0; i < N; ++i) {
        // scan each row pixel by pixel from left to right
        COL:for (int j = 0; j <M; ++j) {
            // get values of the pixels in the kernel
            p1 = (j > 1) ? img[i][j-2]: 0;
            p2 = (j > 0) ? img[i][j-1]: 0;
            p3 = img[i][j];
            p4 = (j < M-1) ? img[i][j+1]: 0 ;
            p5 = (j < M-2) ? img[i][j+2]: 0 ;
            // compute the mean
            out_orig[i][j] = (p1 + p2 + p3 + p4 + p5) / 5;
        }
    }
}

CCS_MAIN(int argc, char* argv[]) {
    //std::srand(time(0));

    for (int example = 0; example < 10; ++example) {
        short img[N][M];
        short out_orig[N][M] = {0};
        //short out_noQ[N][M] = {0};
        short out_Q[N][M] = {0};

        std::cout << "Creating Example Image..." << std::endl;
        //create random image
        if (example == 0) {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < M; ++j) {
                    if ((j > 0) && (j < 40)) {
                        img[i][j] = 200;
                    } else if ((j > 80) && (j < 120)) {
                        img[i][j] = 200;
                    } else {
                        img[i][j] = 0;
                    }
                }
            }
        }else{
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < M; ++j) {
                    img[i][j] = rand() % 255;
                }
            }
        }

        //call All Functions
        original(img, out_orig);
        //no_queue(img,out_noQ);
        with_queue(img, out_Q);

        //check if all outputs are the same
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
//            if (out_orig[i][j] != out_noQ[i][j]){
//                std::cout << "Error in No Queue Output at element" << i <<"," << j << std::endl;
//            }
                if (out_orig[i][j] != out_Q[i][j]) {
                    std::cout << "Error in With Queue Output at element" << i << "," << j << std::endl;
                }
            }
        }
        std::cout << "Checking Complete..." << std::endl;
    }
    CCS_RETURN(0);
}