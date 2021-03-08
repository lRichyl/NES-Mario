#pragma once

struct Timer{
     Timer();
     double startingTime;
     double finalTime;
     double timeDifference;
     double timeSum;
     bool timeReached = false;

     void countTo(float timeInMilliseconds);
};
