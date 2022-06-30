#include<stdio.h>
#include<stdlib.h>

int checkSafe(int need[], int available[], int m){
    for(int i=0; i<m; i++){
        if(need[i] > available[i]) return 0;
    }
    return 1;
}

void checkSafeState(int m, int n, int available[m], int alloc[n][m], int need[n][m], int total[m]){
    int sequence[n];
    printf("Enter a sequence: ");
    for(int i=0; i<n; i++) scanf("%d", &sequence[i]);
    
    for(int i=0; i<n; i++){
        int index = sequence[i];

        if(checkSafe(need[index], available, m)){
            for(int j=0; j<m; j++) available[j] += alloc[index][j];
        }
        else break;
    }

    for(int j=0; j<m; j++){
        if(available[j] != total[j]){
            printf("The given sequence is not in a SAFE STATE\n");
            return;
        }
    }
    printf("The given sequence is in a SAFE STATE\n");
}

int calcSafeState(int m, int n, int available[m], int alloc[n][m], int need[n][m]){
    int terminated[n], safeState[n], index=0;
    for(int i=0; i<n; i++) terminated[i] = 0;

    for (int k=0; k<n; k++){
        for (int i=0; i<n; i++){
            if(terminated[i] == 0){
                int flag = 1;
                for (int j = 0; j<m; j++){
                    if (need[i][j] > available[j]){
                        flag = 0;
                        break;
                    }
                }
                if(flag){
                    for (int j=0; j<m; j++){
                        available[j] += alloc[i][j];
                    }
                    terminated[i] = 1;
                    safeState[index++] = i;
                }
            }
        }
    }

    if(index == n){
        printf("Sequence of process that is SAFE STATE:\n"); 
        for (int i=0; i<n-1; i++) 
            printf(" P%d ->", safeState[i]); 
        printf(" P%d\n", safeState[n - 1]); 

        printf("System is not in Deadlock\n");
        return 1;
    }
    
    printf("System is in Deadlock\nNo sequence of process in SAFE STATE\n");
    return 0;
}

int resourceRequest(int m, int n, int available[m], int alloc[n][m], int need[n][m]){
    int index;
    printf("Enter process number: ");
    scanf("%d", &index);

    int request[m];
    printf("Enter resource request of P%d: ", index);
    for(int j=0; j<m; j++) scanf("%d", &request[j]);

    //check with need
    for(int j=0; j<m; j++){
        if(request[j] > need[index][j]) return 0;
    }

    //check with available
    for(int j=0; j<m; j++){
        if(request[j] > available[j]) return 0;
    }

    for(int j=0; j<m; j++){
        available[j] -= request[j];
        alloc[index][j] += request[j];
        need[index][j] -= request[j];
    }

    //using calcSafeState function as a check
    int flag = calcSafeState(m, n, available, alloc, need);
    if(flag) return 1;
    return 0;
}

int main()
{
    int m,n;
    printf("Enter no. of processes: ");
    scanf("%d", &n);
    printf("Enter no. of resources: ");
    scanf("%d", &m);

    int alloc[n][m];
    printf("Enter AllocTable:\n");
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++) scanf("%d", &alloc[i][j]);
    
    int max[n][m];
    printf("Enter MaxTable:\n");
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++) scanf("%d", &max[i][j]);

    int total[m];
    printf("Enter total instances of each of the %d resource types: ", m);
    for(int i=0; i<m; i++) scanf("%d", &total[i]);

    //calculate need
    int need[n][m];
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    //calculate available
    int available[m], sum[m];
    for(int i=0; i<m; i++) sum[i] = 0;

    for(int j=0; j<m; j++){
        for(int i=0; i<n; i++) sum[j] += alloc[i][j];
        available[j] = total[j] - sum[j];
    }

    int flag;
    char choice;
    printf("Enter choice: ");
    scanf(" %c", &choice);
    switch(choice){
        case 'a':
            flag = calcSafeState(m, n, available, alloc, need);
            break;
        case 'b':
            checkSafeState(m, n, available, alloc, need, total);
            break;
        case 'c':
            flag = resourceRequest(m, n, available, alloc, need);
            if(flag) printf("Resource granted\n");
            else printf("Resource not granted\n");
            break;
        default:
            printf("Please enter a valid choice.\n");
            break;
    }

    return 0;
}
