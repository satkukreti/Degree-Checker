# Degree Checker

A text based application that can be fed a prerequisites file to ensure that a student's schedule is valid using an unordered_map. The program also has waitlist capabilities through the use of a max heap. The goal of this project was to:

- Learn how to utilize maps in storing relational data
- Ensure that courses are taken in the proper chronological order while fulfilling all prerequisites
- Check whether prerequisites form a cycle and to reject that data
- Create a working waitlist based on a max heap

## Introduction

Graphs are versitile data structures that can be used to represent networks of communication, data organization, machine learning, etc. This program utilizes their functionality to create a working degree checker. A student can build their 4 year schedule and compare it to their university's requirements using standard spring, summer, and fall semester courses.

To create a file, put the name of the semester or course at the start of each line, and then the appropriate classes or prerequisites. The semsters do not have to be in chronological order, as the code is smart enough to peice them in the correct order during runtime. *After all, the order in which the data is fed matters when cross checking with the prerequisites.*

This application has built in error checking for the prerequisites - it can see whether the courses form a cyclic graph. For example, assume that you want to take a class called `CS210` and it needs you to take `CS110` beforehand. Now, assume that `CS110` has `CS210` as a prerequisite also. The program would reject this input as it creates a cycle and thus makes no sense.

Lastly, there is a waitlist functionality. Through the use of a max heap, the code keeps track of `Students` who are waitlisted for the classes they want. Using a point system, the student with the highest points is enrolled into the class while the heap does a `heapifyUp` to maintain the max heap.

This project has more error checking running in the background. For example, if a course does not exist, or if a student was not mentioned, etc.

## Makefile

Contains the following targets:

- `clean` Removes all the files Makefile can create
- `waitlist` - creates the waitlist executable from Waitlist, ScheduleCheck, and PrereqCheck

## Runtime Example

## Aknowledgements

This was my favorite (and last) project in CS310. The credit for this idea goes to Professor Mike Lewis of Binghamton University. The implementation of the code was completely my own.




