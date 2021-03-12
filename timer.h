#pragma once

//DO NOT USE A TIMER INSIDE A LOOP CONTROLLED BY A TIMER
//THIS CAUSES ISSUES
//In those cases use deltaTfixed to count time
struct Timer{
     Timer();
     double startingTime;
     double finalTime;
     double timeDifference;
     double timeSum;
     bool timeReached = false;

     void countTo(float timeInMilliseconds);
};
