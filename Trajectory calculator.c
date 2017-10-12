#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

/*
 _____         _           _                               _            _       _
|_   _|       (_)         | |                             | |          | |     | |
  | |_ __ __ _ _  ___  ___| |_ ___  _ __ _   _    ___ __ _| | ___ _   _| | __ _| |_ ___  _ __
  | | '__/ _` | |/ _ \/ __| __/ _ \| '__| | | |  / __/ _` | |/ __| | | | |/ _` | __/ _ \| '__|
  | | | | (_| | |  __/ (__| || (_) | |  | |_| | | (_| (_| | | (__| |_| | | (_| | || (_) | |
  \_/_|  \__,_| |\___|\___|\__\___/|_|   \__, |  \___\__,_|_|\___|\__,_|_|\__,_|\__\___/|_|
             _/ |                         __/ |
            |__/                         |___/
*/

float g=9.81,pi=3.141592653589793238462643383279;  //define some general constants used in computation
long c_light = 299792458;                          //


float root(double v,double theta,float y_0){
    int d;
    theta = theta/180*pi;       //convert to radians
    d = pow(v,2)/(2*g)*(1+sqrt(1+(2*g*y_0)/(pow(v,2)*pow(sin(2*theta),2))))*sin(2*theta);
    return(d);
}

int print_table(double v,double theta,float y_0,int nDigits_list[2]){

     //the below print"function" displays how the travel distance would vary when
    //2 of the variables are kept constant and 1 changes, this gives a nice overview
    //of what would happen if a variable were changed.

    //Note that the height and velocity tables are dependent on the input of the user
    //if for example height=1000 is entered it will print in the range of 1000->17000
    //and when height=35 in entered it will print in the range of 10->1700
    //same goes for the velocity

    int i,j,distance_table1,distance_table2,distance_table3;
    double theta_table,height_table,velocity_table;
    char angles[] = "angle", dist[] = "distance", vel[] = "velocity", height[] = "height";

    printf("%7s | %7s %12s | %7s %13s | %7s\n",angles,dist,height,dist,vel,dist);
    printf("___________________________________________________________________\n");
    for(i=1;i<17;i+=1){
        theta_table = i*5;
        height_table = i*(pow(10,nDigits_list[0]-1));
        velocity_table = i*(pow(10,nDigits_list[1]-1));
        distance_table1 = root(v,theta_table,y_0);
        distance_table2 = root(v,theta,height_table);
        distance_table3 = root(velocity_table,theta,y_0);
        printf("%6d\370 | %6d m %10d m | %6d m %9d m/s | %6d m\n",(int) theta_table,distance_table1,(int) height_table,distance_table2,(int) velocity_table,distance_table3);
    }

}

int digits_check(double v,float y_0,int k){ //calculates how many decimals a number is
    int nDigits_list[2];
    nDigits_list[0] =floor(log10(abs(y_0)))+1;
    nDigits_list[1] = floor(log10(abs(v)))+1;
    return nDigits_list[k];
}


int main(){
    bool calculate = true, input_OK = true;
    int distance;
    float y_0;
    double v,theta;
    printf("This program calculates the horizontal distance travelled by a projectile.\n\n");
    printf("Please provide the initial speed and height and the launch angle of the projectile.\n\n");

    while(calculate==true){

    do {            //check for wrong inputs and give advise on the formatting
        input_OK = true;
        printf("Initial speed [m/s]: ");
        fflush(stdin);
        if(scanf("%lf",&v) != 1) {
            printf("Input is not a number!\n");
            input_OK = false;
        };
        if(v <= 0) {
            printf("Negative values are not accepted!\n");
            input_OK = false;
        }
        else if(v > c_light) {
            printf("Nothing can travel faster than the speed of light!\n");
            input_OK = false;
        }
    } while(input_OK == false);
    do {
        input_OK = true;
        printf("Initial height [m]: ");
        fflush(stdin);
        if(scanf("%f",&y_0) != 1) {
            printf("Input is not a number!\n");
            input_OK = false;
        }
        if(y_0 < 0) {
            printf("Only positive values are allowed!\n");
            input_OK = false;
        }
    } while(input_OK == false);

    do {
        input_OK = true;
        printf("Launch angle [degrees]: ");
        fflush(stdin);
        if(scanf("%lf",&theta) != 1) {
            printf("Input is not a number!\n");
            input_OK = false;
        };
        if(theta >= 90 || theta <= 0) {
            printf("Pick a value in between 0 and 90 degrees!\n");
            input_OK = false ;
        }
    } while(input_OK == false);

    distance = root(v,theta,y_0);

    int nDigits_list[2];
    nDigits_list[0] = digits_check(v,y_0,0);
    nDigits_list[1] = digits_check(v,y_0,1);

    printf("The distance traveled by the projectile is:  ");
    printf("%d m",distance);

    printf("\n\nFor a sensitivity check you can take a look at the tables below.\n\n");

    print_table(v,theta,y_0,nDigits_list);
    printf("\n\n");

    printf("Press 1 to start a new trajectory calculation and press 2 to quit.\n");
    bool end = false;
    while(end == false){
        int input_sw;
        fflush(stdin);
        scanf("%d",&input_sw);
        switch(input_sw){
            case 1:
                system("cls");
                end = true;
                break;
            case 2:
                end = true;
                calculate = false;
                break;
            default:
                printf("Wrong input, try again.\n");
        }
    }

    }
    return(0);

}
