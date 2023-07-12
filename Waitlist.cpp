#include <queue>
#include <bits/stdc++.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include "scheckCopy.cpp"

using namespace std;

struct Student {
	string bnum;
   int priorityPoints;
};

class Students {
	private:
   	vector<Student> heap;
	
	public:
		vector<Student> getheap() {
			return heap;		
		}
		
		bool find(string bnum) {
			for(int i = 0; i < (int)heap.size(); i++) {
				if(bnum == heap.at(i).bnum) {
					return true;				
				}			
			}
			return false;		
		}
		
 		void insert(string bnum, int p) {
 			Student temp;
 			temp.bnum = bnum;
 			temp.priorityPoints = p;
 			heap.push_back(temp); 			
 			heapifyUp(heap.size() - 1);
 		}
    	
    	//just adds points to the person on the waitlist
    	void promote(int points, string bnum) { 
        	// Find the index of the current student within the heap
        	int index = -1;
        	for (int i = 0; i < (int)heap.size(); i++) {
         	if (heap[i].bnum == bnum) {
                index = i;
                heap[i].priorityPoints += points;
                break;
            }
        }
        	if (index != -1) {
         	heapifyUp(index);
      	}
    	}
    	
    	Student getMax() {
      	if (heap.empty()) {
         	throw "Waitlist is empty";
        	}
        	return heap[0];
    	}

	   void heapifyUp(int index) {
      	while (index > 0) {
      		int parentIndex = (index - 1) / 2;
      		if (heap[index].priorityPoints <= heap[parentIndex].priorityPoints)
         		return;
      		else {
         		swap(heap[index], heap[parentIndex]);
         		index = parentIndex;
      		}
   		}	
   	}
    	
    	void heapifyDown(int index) {
      	int childIndex = 2 * index + 1;
      	int value = heap[index].priorityPoints;

   		while (childIndex < (int)heap.size()) {
      		// Find the max among the node and all the node's children
      		int maxValue = value;
      		int maxIndex = -1;
      		for (int i = 0; i < 2 && i + childIndex < (int)heap.size(); i++) {
         		if (heap[i + childIndex].priorityPoints > maxValue) {
            		maxValue = heap[i + childIndex].priorityPoints;
            		maxIndex = i + childIndex;
         		}
      		}

      		if (maxValue == value) {
         		return;
      		} else {
         		swap(heap[index], heap[maxIndex]);
         		index = maxIndex;
         		childIndex = 2 * index + 1;
      		}
   		}
   	}
   
   	Student extractMax() {
     		if (heap.empty()) {
 				throw "Waitlist is empty";
   		}
   		Student temp = heap[0];
   		
   		Student putBack = temp;
   		putBack.priorityPoints = 0;
   		
   		heap.erase(heap.begin());
   		heap.push_back(putBack);
   		
   		heapifyDown(0);
   		return temp;
		}

};

int main (int argc, char* argv[]) {
	if(argc != 5){
		cout << "Incorrect # of args" << endl;
		exit(0);	
	}
	
	string semester = argv[1];
  	string prereqfile = argv[2];
  	string schedsfile = argv[3];
  	string enrollmentfile = argv[4];
  	Students s;

  	regex semSeason ("^[0-9]{4}(Spring|Summer|Fall)$");
  	if (!(regex_match (semester, semSeason))) {
   	cout << "Invalid semester" << endl;
      return 1;
   }

  	string line;
  	ifstream schedulesFile(schedsfile);
  	if (schedulesFile.is_open()) {
    	ScheduleCheck sch_check = ScheduleCheck(prereqfile);
		regex bNumber("^(B[0-9]{8}$)");
      while (getline(schedulesFile, line)) {
      	if(regex_match(line.substr(0, 9), bNumber)) {
      		s.insert(line.substr(0, 9), 0);
      	} else {
				cout << "Incorrect BNumber: " << line.substr(0, 9) << endl;
				return 0;	
      	}
	  		string filename = line.substr(line.find(" ") + 1);
			cout << "Processing file: " << filename << endl;  			  		
	  		sch_check.readFile(filename);
	  		sch_check.reset();
		}
   } else {
   	cout << "Unable to open file";
   	return 0;
   }
   schedulesFile.close();
  	
  	ifstream enrollment (enrollmentfile);
  	if (!enrollment.is_open ()) {
     	cout << "Failed to open file: " << enrollmentfile << endl;
      return 0;
   }

  // Map to store max heaps for each course
  unordered_map<string, Students> courses;

  // Read file line by line
  string theLine;
  while (getline(enrollment, theLine)) {
      // Split line by space
      vector<string> separatedCommand;
      size_t locationOfSpace;

      while ((locationOfSpace = theLine.find (" ")) != string::npos) {
	  		separatedCommand.push_back (theLine.substr (0, locationOfSpace));
	  		theLine.erase(0, locationOfSpace + 1);
		}
		separatedCommand.push_back(theLine);
      // Check command and perform appropriate operation on corresponding max heap
      if (separatedCommand[0] == "newlist") {
      	//cout << separatedCommand.size();
			if (separatedCommand.size() != 2) {
	     		cout << "Error: Insufficient arguments for newlist command." << endl;
	      	exit(0);
	    	}
			
			Students ss = Students();		  
		  courses[separatedCommand[1]] = ss;
		} else if (separatedCommand[0] == "add") {
		  // Check if there are enough arguments
		  if (separatedCommand.size () != 4) {
	     	cout << "Error: Insufficient arguments for add command." << endl;
	      exit(0);
	    }
		  // Parse arguments
		  string bnumber = separatedCommand[1];
		  string course = separatedCommand[2];
		  int weight = stoi(separatedCommand[3]);
			
		if(courses.find(course) == courses.end()) {
			cout << "The course is not yet created\nEnding program...\n";
			exit(0);
		}
		  // Add student to corresponding max heap
			if(s.find(bnumber)) {
				courses[course].insert(bnumber, weight);
			} else {
				cout << "The Student was not mentioned before\nEnding program...\n";
				exit(0);
			}
		} else if (separatedCommand[0] == "promote") {
		  if (separatedCommand.size () != 4) {
	      cout << "Error: Insufficient arguments for promote command." << endl;
	      continue;
	    }
		  // Parse arguments
		  string bnumber = separatedCommand[1];
		  string course = separatedCommand[2];
		  int weight = stoi(separatedCommand[3]);
	
			if(courses.find(course) == courses.end()) {
				cout << "The course is not yet created\nEnding program...\n";
				exit(0);
			}
		  // Add student to corresponding max heap
			if(s.find(bnumber)) {
				courses[course].promote(weight, bnumber);
			} else {
				cout << "The Student was not mentioned before\nEnding program...\n";
				exit(0);
			}
		} else if (separatedCommand[0] == "enroll") {
	  		if (separatedCommand.size () != 2) {
	      	cout << "Error: Insufficient arguments for enroll command." << endl;
	      	continue;
	    	}
	    	string course = separatedCommand[1];
	    	
	    	if(courses.find(course) == courses.end()) {
				cout << "The course is not yet created\nEnding program...\n";
				exit(0);
			}

	    	Student lucky = courses[course].extractMax();
	    	cout << "Enrolling student " << lucky.bnum << " in course " << course << endl;

	}
   }
};