#include <stdio.h>
#define GRID_WIDTH 8
#define GRID_HEIGHT 5

int min(int a, int b)
{
    return a < b ? a : b;
}

// black squares are represented with 1
// white squares are represented with 0
// input for example a
/*

1 0 0 0 0 0 0 0
1 0 0 1 0 0 0 1
1 0 0 1 1 0 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1

*/

// input for example b
/*

1 0 0 0 0 0 0 1
1 0 0 1 0 0 0 1
1 0 1 1 0 0 1 1
1 1 1 1 0 0 1 1
1 1 1 1 1 1 1 1

*/

int count_water_cells(int h[GRID_WIDTH])
{
    int left_idx = 0, right_idx = -1;
    int water = 0;
    int target_h = *h;

    while (left_idx < GRID_WIDTH)
    {
        // starting with the first column, look for a
        // column with the same or greater height,
        // because the water will spill if the other
        // height is smaller
        for (int _ = left_idx + 1; _ < GRID_WIDTH; _++)
        {
            if (h[_] >= target_h)
            {
                // matching height found, proceed to
                // calculate the number of water cells
                right_idx = _;
                break;
            }
        }

        if (right_idx < 0 && target_h > 0)
        {
            // the target height wasn't found,
            // decrement it and try again with
            // the new target height
            target_h--;
            continue;
        }
        else if (target_h == 0)
        {
            // all heights were tried and
            // no match was found,
            // move on to the next column
            target_h = h[++left_idx];
            continue;
        }

        // the number of cells between the
        // left and right column
        int between_h = 0;
        for (int _ = left_idx + 1; _ < right_idx; _++)
        {
            between_h = between_h + h[_];
        }

        // calculate the number of water cells
        // between the left and right column
        water = water + (right_idx - left_idx - 1) * min(h[left_idx], h[right_idx]) - between_h;

        left_idx = right_idx; // the right column is the new left column
        right_idx = -1;       // reset the right column index

        target_h = h[left_idx]; // and also update the target height
    }

    return water;
}

int main(void)
{
    int grid[GRID_HEIGHT][GRID_WIDTH];
    int h[GRID_WIDTH];

    for (int i = 0; i < GRID_HEIGHT; i++)
        for (int j = 0; j < GRID_WIDTH; j++)
        {
            scanf("%d", &grid[i][j]);
            h[j] = h[j] + grid[i][j];
        }

    printf("Water cells: %d\n", count_water_cells(h));
    return 0;
}
