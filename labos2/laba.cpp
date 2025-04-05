#include <windows.h>
#include <stdio.h>

volatile long Var = 0;

DWORD WINAPI Inc(LPVOID lpParam) {
    volatile long* pVar = (volatile long*)lpParam;
    for (int i = 0; i < 100000000; i++) {
        (*pVar)++;
    }
    return 0;
}

DWORD WINAPI Dec(LPVOID lpParam) {
    volatile long* pVar = (volatile long*)lpParam;
    for (int i = 0; i < 100000000; i++) {
        (*pVar)--;
    }
    return 0;
}
int main() {
    HANDLE threads[20];

    printf("Var: %ld\n", Var);

    for (int i = 0; i < 10; i++) {
        threads[i] = CreateThread(
            NULL,                  
            0,                      
            Inc,      
            (LPVOID)&Var,           
            0,                    
            NULL                   
        );

    }

    for (int i = 10; i < 20; i++) {
        threads[i] = CreateThread(
            NULL,
            0,
            Dec,
            (LPVOID)&Var,
            0,
            NULL
        );
    }

    WaitForMultipleObjects(20, threads, TRUE, INFINITE);
    for (int i = 0; i < 20; i++) {
        CloseHandle(threads[i]);
    }
    printf("Final Var: %ld\n", Var);

    return 0;
}
