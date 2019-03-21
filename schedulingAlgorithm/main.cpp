/****************************************************************************************************************
*Name: Ribash Sharma												*
*Class: Operating System											*
*Instructor: Dr. Chao Zhao											*
*Description: This program implements four different scheduling algorithm like shortest job first, First come   *
*	      First Serve, Priority Based and round robin algorithm for two quantum and calculates the the 	*
*	      average waiting time and turn around time for all those algorithms for dseterminging the 		*	
*	      efficiency											*
****************************************************************************************************************/
#include <iostream>
#include "processes.h"
#include <stdlib.h>
#include <iomanip>
using namespace std;
int main()
{
	float awFCFS = 0;
	float atFCFS = 0;
	float awSJF = 0;
	float atSJF = 0;
	float awPBA =0;
	float atPBA = 0;
	float awRRFive = 0;
	float atRRFive = 0;
	float awRREight = 0;
	float atRREight = 0;	


	  srand(time(NULL));

	  for (int i = 0; i < 100; i++)
		{	/*creates a process and initializes them*/
			
			processList A;
                	A.generateListOfProcess();
                
			/* Implements the algorithm based on the requirement*/
			A.FCFS();
                	A.SJF();
                	A.priorityBasedComparision();
                
			int arrayForFive[2];
                	A.roundRobin(5, arrayForFive);
                	A.totalBurstTimeRR5 = arrayForFive[0];
                	A.totalWaitTimeRR5 = arrayForFive[1];
                
			int arrayForEight[2];
              		A.roundRobin(8, arrayForEight);
               	 	A.totalBurstTimeRR8 = arrayForEight[0];
                	A.totalWaitTimeRR8 = arrayForEight[1];

			A.conversion();
 
			atFCFS += A.totalBurstTimeFCFS;
			awFCFS += A.totalWaitTimeFCFS;

			atSJF += A.totalBurstTimeSJF;
			awSJF += A.totalWaitTimeSJF;

			atPBA += A.totalBurstTimePCB;
			awPBA += A.totalWaitTimePCB;

			atRRFive += A.totalBurstTimeRR5;
			awRRFive += A.totalWaitTimeRR5;

			atRREight += A.totalBurstTimeRR8;
			awRREight += A.totalWaitTimeRR8;				

			/*Prints the individual report*/        	
			if(i<3)
			{
				cout<<"            Run "<<i+1<<"       "<<endl;
				A.printIndividual();
			} 
	        }

	cout<<"          Final report                    "<<endl;
        cout<<"------------------------------------------"<<endl;
        cout<<"|        |   Overall AWT  | Overall ATT  |"<<endl;
        cout<<"------------------------------------------"<<endl;
        cout<<"|"<<setw(8)<<"FCFS"<<setw(1)<<"|"<< setw(7)<< awFCFS/100 <<setw(9)<<"|"<< setw(7)<< atFCFS/100 <<setw(9)<<"|"<<endl;
        cout<<"|"<<setw(8)<<"SJF"<<setw(1)<<"|"<< setw(7)<<  awSJF/100  <<setw(9)<<"|"<< setw(7)<<atSJF/100<<setw(9)<<" |"<<endl;
        cout<<"|"<<setw(8)<<"RR 5"<<setw(1)<<"|"<< setw(7)<< awRRFive/100 <<setw(9)<<"|"<< setw(7)<<awRRFive/100<<setw(9)<<"|"<<endl;
        cout<<"|"<<setw(8)<<"RR 8"<<setw(1)<<"|"<< setw(7)<< awRREight/100 <<setw(9)<<"|"<< setw(7)<<awRREight/100<<setw(9)<<"|"<<endl;
        cout<<"------------------------------------------"<<endl;
        cout<<endl;

	return 0;
}
