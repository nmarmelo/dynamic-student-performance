/******************************************************************************
file dynamicStudentPerformance.cpp                                            

                      CAIS 0230                            Nathan Marmelo
                      
          PROGRAM DYNAMIC COURSE GRADES
          =============================
This program uses pointers and dynamic arrays to process test scores of students
enrolled in a class. It is written so that the size of the arrays can vary for 
each execution of the program. 
After the names of the students and their test scores are obtained, the program 
will send the names and corresponding test scores to both the screen and an 
external text file, "results.txt". The test scores will then be sorted into 
ascending order using the selection sort algorithm.
Once the scores have been sorted, the program will provide a list of student 
names and corresponding test scores sorted in ascending order of the test scores
to both the screen and external text file.
It will additionally compute the average test score, to two digits of precision.
******************************************************************************/

//start

#include<iostream>
#include<iomanip>
#include<cctype>
#include<cstdlib>
#include<fstream>
#include<string>
using namespace std;






int main(){
    //int*testsptr;
    int numTestScores;                            //number of test scores/students
    string*namesPtr;                                 //pointer to array of names
    double*testScoresPtr;                            //pointer to array of testScores 
    
    //function prototypes
    void describeprogram();
    string* GetStudentNames(int& numTestScores);
    double* GetScores(string *namesPtr, int numTestScores);
    void sort(string *namesPtr, double *testScoresPtr, int numTestScores);
    void displaySortedListandAverageScore(string *namesPtr, double *testScoresPtr, int numTestScores);
    
    //start
    describeprogram();                          //describe program to user
    cin>>numTestScores;                         //get num of test scores
    cin.ignore();
    namesPtr = GetStudentNames(numTestScores);      //calls get student names to collect and store the student's names                                 
    testScoresPtr = GetScores(namesPtr, numTestScores);        //calls GetScores to collect the scores for each student
    sort(namesPtr, testScoresPtr, numTestScores);           //calls sort to order the students by ascending test score
    displaySortedListandAverageScore(namesPtr, testScoresPtr, numTestScores);     //prints the sorted list of students to screen and an external file
    
    system("PAUSE");
    return 0;
}

//**************************************************
// Function describeprogram                        *
// This function describes the program to the user.*
//**************************************************

void describeprogram(){
     cout<<"Enter the number of tests, followed by the names and test scores of each"<<endl;
     cout<<"student. The program will sort the students into ascending order by score"<<endl;
     cout<<"and send the results to the screen and an external text file, 'results.txt'."<<endl;
     cout<<"It will additionally calculate the average test score, to two decimal places"<<endl;
     cout<<"Enter the number of students to begin!"<<endl;
}

//********************************************************
// Function GetStudentNames                              *
// This function takes as input, &numTestScores, that is *
// used to create a dynamic array. It will prompt the    *
// user to enter the names of as many students as there  *
// are test scores.                                      *
//********************************************************

string* GetStudentNames(int &numTestScores){

     string* names;
     names = new string[numTestScores];
        
     for(int i =0; i<numTestScores; i++)    //prompt user to enter a name until end of array
     {
          cout<<"Enter the name of student "<<(i+1)<<":";
          getline(cin, names[i]);
          //cin.ignore();
     }
     return names;
}

//********************************************************
// Function GetScores                                    *
// a function that takes in the pointer to the array     *
// of student names and the number of test scores as     *
// arguments and returns through its name a pointer      *
// to the array of test scores. The body of the func     *
// -tion prompts for the test score of each student      *
// by name. Once the scores are properly obtained,       *
// the function is to report to both the screen and      *
// the external text file, "results.txt", the list       *
// of names of the students and their corresponding      *
// test scores in unsorted order and in tabular          *
// format. the Test scores are to be sent to two         *
// digits of precision to the right of the decimal point *
//********************************************************

double* GetScores(string* namesPtr, int numTestScores){
     ofstream outs;
     outs.open("results.txt", ios::out);
     
     double* scores;
     scores = new double[numTestScores];
     
     for(int i = 0; i < numTestScores; i++){
          cout<<"Enter score for "<<namesPtr[i]<<": ";
          cin>>scores[i];
     }
     
     cout<<"\n"<<left<<setw(30)<<"Name"<<"|\tTest Score "<<endl<<endl;
     outs<<"\n"<<left<<setw(30)<<"Name"<<"|\tTest Score "<<endl<<endl;
     for(int i =0; i < numTestScores; i++){
           cout<<left<<setw(30)<<namesPtr[i]<<"|   "<<scores[i]<<endl; 
           outs<<left<<setw(30)<<namesPtr[i]<<"|   "<<scores[i]<<endl;      
     }
     
     outs.close();
     return scores;
}

// ********************************************************
// The sort function performs a selection sort on the     *
// arrays pointed to by the name and score parameters     *
// into ascending order. The size parameter holds the     *
// number of elements.                                    * 
// ********************************************************
void sort(string* namesPtr, double* testScoresPtr, int numTestScores)
{
	int startScan, minIndex;
	string minName;
	double minValue;

	for (startScan = 0; startScan < (numTestScores - 1); startScan++)
	{
		minIndex = startScan;
		minValue = testScoresPtr[startScan];
		minName = namesPtr[startScan];
      
		for(int index = startScan + 1; index < numTestScores; index++)
		{
			if (testScoresPtr[index] < minValue)
			{
				minValue = testScoresPtr[index];
				minName = namesPtr[index];
				minIndex = index;
			}
		}
      
		testScoresPtr[minIndex] = testScoresPtr[startScan];
		namesPtr[minIndex] = namesPtr[startScan];
      
		testScoresPtr[startScan] = minValue;
		namesPtr[startScan] = minName;
	}
}

// ********************************************************
// A function that takes in through its arguments the     *
// pointer to the array of student names, the pointer to  *
// the corresponding sorted list of test scores, and the  *
// number of test scores, and sends to both the screen and*
// external file, "results.txt", the list of names and    *
// test scores along with the average test score, which is*
// computed in the body of the function. All test scores  *
// and the average test score are to be shown to two      *
// digits of precision to the right of the decimal point  *
// ********************************************************
void displaySortedListandAverageScore(string* namesPtr, double* testScoresPtr, int numTestScores){
     ofstream outs;
     outs.open("results.txt", ios::out);
     
     double average = 0;
     cout<<"\n\n\n\n";
     cout<<"Sorted List and Average Score\n";
     outs<<"Sorted List and Average Score\n";
     cout<<left<<setw(30)<<"Name"<<"|\tTest Score "<<endl<<endl;
     outs<<left<<setw(30)<<"Name"<<"|\tTest Score "<<endl<<endl;
     
     for(int i =0; i < numTestScores; i++){
           cout<<left<<setw(30)<<namesPtr[i]<<"|   "<<testScoresPtr[i]<<endl; 
           outs<<left<<setw(30)<<namesPtr[i]<<"|   "<<testScoresPtr[i]<<endl;  
           average+=testScoresPtr[i];    
     }
     
     average = (average/numTestScores);
     cout<<"\nAverage test score:\t"<<setprecision(4)<<average<<endl;
     outs<<"\nAverage test score:\t"<<setprecision(4)<<average<<endl;
     outs.close();
}



