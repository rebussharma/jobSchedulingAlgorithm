/****************************************************************************************************************
*Name: Ribash Sharma                                                                                            *
*Class: Operating System                                                                                        *
*Instructor: Dr. Chao Zhao                                                                                      *
*Description: This program implements four different scheduling algorithm like shortest job first, First come   *
*             First Serve, Priority Based and round robin algorithm for two quantum and calculates the the      *
*             average waiting time and turn around time for all those algorithms for dseterminging the          *
*             efficiency                                                                                        *
****************************************************************************************************************/

//************************************** Including Libraries ****************************************************
#include <iostream>
#include "processes.h"
#include <stdlib.h>
#include <algorithm>
#include <time.h>
#include <iomanip>
using namespace std;

//*****************************************************************************************************************

void processList::printIndividual() /*Prints the report containing average waiting time and average turn around time*/
{
	cout<<" ---------------------------------"<<endl;
	cout<<"|     |   AWT       |   ATT       |"<<endl;
	cout<<"----------------------------------"<<endl;
	cout<<"|"<<setw(5)<<"FCFS"<<setw(1)<<"|"<< setw(7)<<totalWaitTimeFCFS <<setw(7)<<"|"<< setw(7)<<totalBurstTimeFCFS <<setw(7)<<"|"<<endl;
        cout<<"|"<<setw(5)<<"SJF"<<setw(1)<<"|"<< setw(7)<<totalWaitTimeSJF<<setw(7)<<"|"<< setw(7)<<totalBurstTimeSJF<<setw(7)<<" |"<<endl;
        cout<<"|"<<setw(5)<<"PCB"<<setw(1)<<"|"<< setw(7)<<totalWaitTimePCB<<setw(7)<<"|"<< setw(7)<<totalBurstTimePCB<<setw(7)<<" |"<<endl;
	cout<<"|"<<setw(5)<<"RR 5"<<setw(1)<<"|"<< setw(7)<<totalWaitTimeRR5<<setw(7)<<"|"<< setw(7)<<totalBurstTimeRR5<<setw(7)<<"|"<<endl;
	cout<<"|"<<setw(5)<<"RR 8"<<setw(1)<<"|"<< setw(7)<<totalBurstTimeRR8<<setw(7)<<"|"<< setw(7)<<totalBurstTimeRR8<<setw(7)<<"|"<<endl;
	cout<<"----------------------------------"<<endl;
	cout<<endl;
}

//********************************************************************************************************************

void processList::conversion()	/*Convert total waiting time and total burst time to averagewaiting time and average turn around time*/
{
	/*
	Formula: Average Waiting Time = Total Waiting Time / 10
		 Average Turn Around Time = (Total Waiting Time + Total burst Time)/10
	*/

	totalBurstTimeFCFS = ((totalBurstTimeFCFS + totalWaitTimeFCFS))/10;
	totalBurstTimeSJF = ((totalWaitTimeSJF+totalBurstTimeSJF))/10;
	totalBurstTimeRR5 = (totalWaitTimeRR5+totalBurstTimeRR5)/10;
	totalBurstTimeRR8 = (totalWaitTimeRR8+totalBurstTimeRR8)/10;
	totalBurstTimePCB = (totalWaitTimePCB + totalBurstTimePCB)/10;

	totalWaitTimeFCFS = totalWaitTimeFCFS/10;
	totalWaitTimeSJF = totalWaitTimeSJF/10;
	totalWaitTimePCB = totalWaitTimePCB/10;
	totalWaitTimeRR5 = totalWaitTimeRR5/10;
	totalWaitTimeRR8 = totalWaitTimeRR8/10;
}

//*****************************************************************************************************************************

void processList::generateListOfProcess()
{	/*Initializes the vector of object with random values*/     
	for(int i=0; i<10; i++)
        {    
	    listOfProcess.push_back(processInstance());	
            listOfProcess[i].processId = i; 
            listOfProcess[i].cpuArrival = (rand() % 10) + 1; 
            listOfProcess[i].cpuBurst = (rand() % 10) + 1;
            listOfProcess[i].priority = (rand() % 7) +1;
     	    listOfProcess[i].waitTime = 0;
	    listOfProcess[i].recordBurst = 0;	
	   }

}

//***************************************************************************************************************************
void processList::FCFS()
{
	vector <processInstance> fcfsvector = listOfProcess;	//copies the original list of process to a temporary vector
	sort(fcfsvector.begin(), fcfsvector.end(), arrivalComparison()); //sorts the vector on basis of arrival time

        totalBurstTimeFCFS = fcfsvector[0].cpuBurst;
        totalWaitTimeFCFS = 0;

	/* caluclates the total burst time and total wait time*/

	for (int i =1; i<10; i++)
	{	
		fcfsvector[i].waitTime = totalBurstTimeFCFS - fcfsvector[i].cpuArrival;
		totalBurstTimeFCFS += fcfsvector[i].cpuBurst;
		totalWaitTimeFCFS += fcfsvector[i].waitTime; 
	}
	
}

//***************************************************************************************************************************
void processList:: SJF()
{
        vector <processInstance> sjfvector = listOfProcess;	//copies the original list of process to a temporary vector
        sort(sjfvector.begin(), sjfvector.end(), arrivalComparison()); //Sorts the vector on the basis of arrival comparision to get the first arrived process
        sort(sjfvector.begin()+1,sjfvector.end(), burstComparison());	//Reaaranges the vector on the basis of CPU burst once the first arrived process is considered
	
        totalBurstTimeSJF = sjfvector[0].cpuBurst;
        totalWaitTimeSJF = 0;

	/*Calculates the total burst time and total arrival time*/

        for (int i =1; i<10; i++)
        {
                sjfvector[i].waitTime = totalBurstTimeSJF - sjfvector[i].cpuArrival;
                totalBurstTimeSJF  += sjfvector[i].cpuBurst;
                totalWaitTimeSJF += sjfvector[i].waitTime;
        }


}

//**************************************************************************************************************************
void processList:: priorityBasedComparision()
{
        vector <processInstance> pcbvector = listOfProcess;//copies the original list of process to a temporary vector
        sort(pcbvector.begin(), pcbvector.end(), arrivalComparison());  //Sorts the vector on the basis of arrival comparision to get the first arrived process
        sort(pcbvector.begin()+1, pcbvector.end(), priorityComparison()); //Reaaranges the vector on the basis of Priority once the first arrived process is considered


        totalBurstTimePCB = pcbvector[0].cpuBurst;
        totalWaitTimePCB = 0;

        for (int i =1; i<10; i++)
        {
                pcbvector[i].waitTime = totalBurstTimePCB - pcbvector[i].cpuArrival;
                totalBurstTimePCB  += pcbvector[i].cpuBurst;
                totalWaitTimePCB += pcbvector[i].waitTime;
        }


}
//*********************************************************************************************************************************
int * processList:: roundRobin(int quantum, int * valueStorage)
{
	vector <processInstance> rrvector = listOfProcess; //copies the original list of process to a temporary vector

        sort(rrvector.begin(), rrvector.end(), burstComparison()); //Sorts the vector in basis of cpu burst time to calculate maximum burst time

	int rounds = (rrvector[9].cpuBurst)/ quantum; //Calculates the maximum number of rounds on the basis of maximum burst time

        sort(rrvector.begin(), rrvector.end(), arrivalComparison()); //Resorts the vector in the basis of arrival
	int totalBurstTimeRR = 0;
	float totalWaitTimeRR = 0;
	rrvector[0].cpuArrival = 0;
	
	/*First Round is done seperately to deduct the wait time from cpu arrival */

	for(int i=0; i<10; i++)
	{	rrvector[i].waitTime = totalBurstTimeRR - rrvector[i].cpuArrival;
		if(rrvector[i].cpuBurst <= quantum )
		{
			totalBurstTimeRR = totalBurstTimeRR + rrvector[i].cpuBurst;
			totalWaitTimeRR = totalWaitTimeRR + rrvector[i].waitTime;
			rrvector[i].recordBurst = totalBurstTimeRR;
			rrvector[i].cpuBurst = 0;	
		}
		else
		{
			totalBurstTimeRR = totalBurstTimeRR + quantum;
                        totalWaitTimeRR = totalWaitTimeRR + rrvector[i].waitTime;
                        rrvector[i].recordBurst = totalBurstTimeRR;
                        rrvector[i].cpuBurst = rrvector[i].cpuBurst - quantum;
		}
	}
	
	/*Remaining Rounds dont consider arrival time */
	for (int j=0; j<= rounds; j++)
	{	
        	for(int i=0; i<10; i++)
        	{	if(rrvector[i].cpuBurst  != 0)
			{
	       			rrvector[i].waitTime = totalBurstTimeRR - rrvector[i].recordBurst;
                		if(rrvector[i].cpuBurst <= quantum )
                		{
                		        totalBurstTimeRR = totalBurstTimeRR + rrvector[i].cpuBurst;
                       			totalWaitTimeRR = totalWaitTimeRR + rrvector[i].waitTime;
                        		rrvector[i].recordBurst = totalBurstTimeRR;
                        		rrvector[i].cpuBurst = 0;
                		}
                		else
                		{
                	       	   totalBurstTimeRR = totalBurstTimeRR + quantum;
                       	     	   totalWaitTimeRR = totalWaitTimeRR + rrvector[i].waitTime;
                       		   rrvector[i].recordBurst = totalBurstTimeRR;
                        	   rrvector[i].cpuBurst = rrvector[i].cpuBurst - quantum;
		                }
			}
        	}
	}
	/*Assigning total wait time and total burst time calculated from round robin algorithm to pass multiple return values*/
	
	valueStorage[1] = totalWaitTimeRR;
	valueStorage[0] = totalBurstTimeRR;
	
return valueStorage;
}
