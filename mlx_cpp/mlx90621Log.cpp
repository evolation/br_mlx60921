#include "mlx90621.cpp"
#include <signal.h>
#include <stdio.h>
#include <time.h>

void intHandler(int dummy){
//   printf("Exiting...\n");
  exit(0);
}

int main() {
//   printf("deingena 22/06/21 ...\n");
//   return 0;
  signal(SIGINT,intHandler);
  int i,j,k;
  char fileName[64];
  time_t rawtime;
  struct tm *timeinfo;
  // databuffer for IR data
  double calcData[64] = {};
  int16_t dataBuf[64] ={};
  // instantiate sensor
  MLX90621 mlx;
  // initialize sensor
  mlx.init();
  //for(k=1;k<10;k++){
  while(1){
    // get ambient temp and perform calculation
    uint16_t T_amb_r = mlx.readTamb();
    double T_amb = mlx.calcTa(T_amb_r);
    // get full frame
    mlx.readFrame(dataBuf);
    // printf("\n");
    // printf("\n");

    // for(int var = 0;var<64;var++)
    // {
    //     printf("%d ",dataBuf[var]);
    // }
    // printf("\n");
    // calculate pixel temps for full frame
    for(j=0;j<16;j++){
      for(i=0;i<4;i++){
        calcData[j*4+i]=mlx.calcTo(dataBuf[j*4+i],j*4+i);
      }
    }
    // print image number
    // printf("image\n");
    printf("{\"pixels\":{\"array\":[");
    for(i = 0;i<16;i++){
      for(j=0;j<4;j++){
        if(4*i+j<63)
            printf("%0.0f,",calcData[4*i+j]);
        else
            printf("%0.0f]},\"ambient\":%0.1f}",calcData[4*i+j],T_amb);

      }
    }
    return 0;
    // output text file
    //sprintf(fileName,"MLXImage_%d.txt",k);
    //mlx.exportText(calcData,fileName);
    // get time
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    // wait until 10s mark
    while(timeinfo->tm_sec % 10 !=0){
      // get time
      time(&rawtime);
      timeinfo = localtime(&rawtime);
      usleep(500000);
    }
    // output png file
    //sprintf(fileName,"MLXImage_%d.png",k);
    //snprintf(fileName,64,"/balloonLogs/%d.%d.%d_MLX.png",timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);
    //mlx.exportPng(calcData,fileName);
    // wait a bit
    sleep(7);
  }
  return 0;
}

