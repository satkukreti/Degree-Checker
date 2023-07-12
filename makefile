waitlist: Waitlist.o scheckCopy.o prcheckCopy.o
	g++ -Wall -Wextra -g Waitlist.o scheckCopy.o prcheckCopy.o -o waitlist

Waitlist.o: Waitlist.cpp
	g++ -g -Wall -Wextra -c Waitlist.cpp

scheckCopy.o: scheckCopy.cpp
	g++ -g -Wall -Wextra -c scheckCopy.cpp

#-------------

sch_check: ScheduleCheck.o prcheckCopy.o
	g++ -Wall -Wextra -g ScheduleCheck.o prcheckCopy.o -o sch_check

ScheduleCheck.o: ScheduleCheck.cpp
	g++ -g -Wall -Wextra -c ScheduleCheck.cpp

prcheckCopy.o: prcheckCopy.cpp
	g++ -g -Wall -Wextra -c prcheckCopy.cpp

#-------------

pr_check: PrereqCheck.o
	g++ -Wall -Wextra -g PrereqCheck.o -o pr_check

PrereqCheck.o: PrereqCheck.cpp
	g++ -g -Wall -Wextra -c PrereqCheck.cpp

clean:
	rm -f *.o waitlist
	rm -f *.o sch_check
	rm -f *.o pr_check

clear:
	clear 

#2023Fall prerequisites.txt schedules.txt enroll.txt