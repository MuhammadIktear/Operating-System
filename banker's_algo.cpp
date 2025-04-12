#include <iostream>
using namespace std;

int main() {
    int available[3], work[5], max[5][3], allocation[5][3], need[5][3], safe[5], totalres[3];
    char finish[5];
    int i, j, k, totalloc = 0, state, value = 0;

    cout << "Enter Instances of each Resource: ";
    for (i = 0; i < 3; i++) {
        cin >> totalres[i];
    }

    cout << "Enter Maximum resources for each process:\n";
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 3; j++) {
            cout << "Enter process " << i << " Resource " << j + 1 << ": ";
            cin >> max[i][j];
        }
    }

    cout << "Enter number of resources allocated to each Process:\n";
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 3; j++) {
            cout << "Enter the resource R" << j + 1 << " allocated to process " << i << ": ";
            cin >> allocation[i][j];
        }
    }

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 3; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    for (i = 0; i < 5; i++) {
        finish[i] = 'f';
    }

    for (i = 0; i < 3; i++) {
        totalloc = 0;
        for (j = 0; j < 5; j++) {
            totalloc += allocation[j][i];
        }
        available[i] = totalres[i] - totalloc;
        work[i] = available[i];
    }

    cout << "\n Allocated Resources \n";
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 3; j++) {
            cout << allocation[i][j] << " ";
        }
        cout << "\n";
    }

    cout << "\n Maximum Resources \n";
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 3; j++) {
            cout << max[i][j] << " ";
        }
        cout << "\n";
    }

    cout << "\n Needed Resources \n";
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 3; j++) {
            cout << need[i][j] << " ";
        }
        cout << "\n";
    }

    cout << "\n Available Resources: ";
    for (i = 0; i < 3; i++) {
        cout << available[i] << " ";
    }
    cout << "\n";

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 3; j++) {
            if ((finish[i] == 'f') && (need[i][j] <= work[j])) {
                state = 1;
            } else {
                state = 0;
                break;
            }
        }
        if (state == 1) {
            for (j = 0; j < 3; j++) {
                work[j] += allocation[i][j];
            }
            finish[i] = 't';
            safe[value] = i;
            ++value;
        }
        if (i == 4) {
            if (value == 5) {
                break;
            } else {
                i = -1;
            }
        }
    }

    cout << "\n Safe States are: ";
    for (i = 0; i < 5; i++) {
        cout << "P" << safe[i] << " ";
    }

    return 0;
}
