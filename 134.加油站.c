/*
 * @lc app=leetcode.cn id=134 lang=c
 *
 * [134] 加油站
 */

// @lc code=start
#include <stdbool.h>
/*
    startingpoint 出发点
    currentpoint 当前点
    currentgas 当前点油量
*/

int canCompleteCircuit(int* gas, int gasSize, int* cost, int costSize)
{
    if (!gas || !cost || gasSize <= 0 || costSize <= 0) return -1;
    
    int startingpoint = 0;
    bool noAnswer = false;

    while (startingpoint < gasSize && !noAnswer)
    {
        int currentpoint = startingpoint;
        int currentgas = gas[startingpoint];

        while (!noAnswer)
        {
            if (currentgas < cost[currentpoint])
            {
                if (currentpoint < startingpoint) noAnswer = true;
                else startingpoint = currentpoint + 1;
                break;
            }
            currentgas -= cost[currentpoint];
            currentpoint = (currentpoint + 1) % gasSize;
            if (currentpoint == startingpoint)
                return startingpoint;
            currentgas += gas[currentpoint];
        }
    }

    return -1;
}
// @lc code=end

