
#include"Motion.h"
using namespace std;
extern int Final_speed[8] ;

void motion(float axis[5],int max_speed)
   {
    float Forward=axis[4];
        float Slide=axis[0];
        float Rotate=axis[2];
        float Pitch=axis[3]*-1;
        float Up=axis[1]*-1;
        float Roll=0;
//        for (int i =0;i<5 ; i++) {
//            cout<<axis[i]<<" ";
//        }
//        cout<<endl;

       int BFR=(Forward-Slide+Up-Rotate+Roll-Pitch)*max_speed;
       int BFL=(Forward+Slide+Up+Rotate-Roll-Pitch)*max_speed;
       int BBR=(-Forward-Slide+Up+Rotate+Roll+Pitch)*max_speed;
       int BBL=(Forward+Slide-Up-Rotate-Roll-Pitch)*max_speed;
       int TFR=(-Forward-Slide+Up+Rotate+Roll-Pitch)*max_speed;
       int TFL=(-Forward+Slide+Up-Rotate-Roll-Pitch)*max_speed;
       int TBR=(Forward-Slide+Up-Rotate-Roll+Pitch)*max_speed;
       int TBL=(Forward+Slide+Up+Rotate-Roll+Pitch)*max_speed;
       Final_speed[0]=TFR;
       Final_speed[1]=TFL;
       Final_speed[2]=TBR;
       Final_speed[3]=TBL;
       Final_speed[4]=BFR;
       Final_speed[5]=BFL;
       Final_speed[6]=BBR;
       Final_speed[7]=BBL;
       normalize(max_speed);

}

   void normalize(int max_speed)
   {    float MAX =0;
        float scale;
        float max_speedF=max_speed;


       for(int i=0;i<8;i++)
       {
           if(abs(Final_speed[i])>MAX)
                MAX=abs(Final_speed[i]);
       }
        if(MAX>max_speed)
        {
            scale=float(max_speedF/MAX);
            for(int i=0;i<8;i++)
                Final_speed[i]*=scale;

        }

   }
