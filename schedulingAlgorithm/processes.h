/****************************************************************************************************************
*Name: Ribash Sharma                                                                                            *
*Class: Operating System                                                                                        *
*Instructor: Dr. Chao Zhao                                                                                      *
*Description: This program implements four different scheduling algorithm like shortest job first, First come   *
*             First Serve, Priority Based and round robin algorithm for two quantum and calculates the the      *
*             average waiting time and turn around time for all those algorithms for dseterminging the          *
*             efficiency                                                                                        *
****************************************************************************************************************/

#ifndef PROCESSES_H
#define PROCESSES_H
#include <vector>
using  namespace std;
	
class processList	
{
		public:
			/*Structure containing information about process*/
		        
			struct processInstance
		        {
                		int processId;
                		int cpuArrival;
                		int cpuBurst;
                		int priority;
				int waitTime;
				int recordBurst;
        		};

			/*Struct used for sorting a vector in basis of arrival time*/
	
			struct arrivalComparison {
				bool operator()(processInstance const &a, processInstance const &b) const{
					if(a.cpuArrival < b.cpuArrival) return true;
					if(a.cpuArrival>b.cpuArrival) return false;
					
				}
			};

			/*Struct used for sorting a vector in basis of burst time*/

                        struct burstComparison {
                                bool operator()(processInstance const &a, processInstance const &b) const{
                                        if(a.cpuBurst < b.cpuBurst) return true;
                                        if(a.cpuBurst>b.cpuBurst) return false;

                                }
                        };

			/*Struct used for sorting a vector in basis of process*/

                        struct priorityComparison {
                                bool operator()(processInstance const &a, processInstance const &b) const{
                                        if(a.priority < b.priority) return true;
                                        if(a.priority > b.priority) return false;

                                }
                        };

			vector <processInstance> listOfProcess; 

			int totalBurstTimeFCFS;		//Stores the total Burst time from FCFS scheduling algorithm
			float totalWaitTimeFCFS;	//Stores the total wait time from FCFS scheduling algorithm
			int totalBurstTimeSJF;		//Stores the total Burst time from SJF scheduling algorithm
                        float totalWaitTimeSJF;		//Stores the total wait time from SJF scheduling algorithm
			int totalBurstTimePCB;		//Stores the total Burst time from Prority  scheduling algorithm
                        float totalWaitTimePCB;		//Stores the total wait time from priority scheduling algorithm
			int totalBurstTimeRR5;		//Stores the total Burst time from round robin scheduling algorithm with five quantam
			float totalWaitTimeRR5;		//Stores the total Wait time from round robin scheduling algorithm with five quantam
			int totalBurstTimeRR8;		//Stores the total Burst time from round robin scheduling algorithm with eight quantam
			float totalWaitTimeRR8;		//Stores the total Wait time from round robin scheduling algorithm with eight quantam
	
		

		void printIndividual();	//Prints the report of average waiting time and average turn around time for all algorithm
		void generateListOfProcess();	//Initializes the arrays with the random value
		void FCFS();	//Calculates the total burst time and total waiting time using FCFS
		void SJF();	//Calculates the total burst time and total waiting time using SJF
		void priorityBasedComparision();	//Calculates the total burst time and total waiting time using priority based comparision
		void conversion();			//Converts the total burst time and total wait time to average turn around time and average waiting time
                void implementation();			
		int * roundRobin(int quantum, int * storage);	//Calculates the total burst time and total average time using round robin
};

#endif
