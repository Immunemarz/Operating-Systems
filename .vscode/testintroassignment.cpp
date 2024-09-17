#include <iostream>
#include <windows.h>
#include <vector>

using namespace std;

int main() {
    vector<PROCESS_INFORMATION> processInfos;
    int numProcesses = 4;

    for (int i = 0; i < numProcesses; ++i) {
        STARTUPINFO si;
        PROCESS_INFORMATION pi;
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));

        // Create a child process
        if (!CreateProcess(NULL,   // No module name (use command line)
            (LPSTR)"notepad.exe",  // Command line
            NULL,                  // Process handle not inheritable
            NULL,                  // Thread handle not inheritable
            FALSE,                 // Set handle inheritance to FALSE
            0,                     // No creation flags
            NULL,                  // Use parent's environment block
            NULL,                  // Use parent's starting directory 
            &si,                   // Pointer to STARTUPINFO structure
            &pi)                   // Pointer to PROCESS_INFORMATION structure
        ) {
            cerr << "CreateProcess failed (" << GetLastError() << ")." << endl;
            return 1;
        }

        processInfos.push_back(pi);
        cout << "Child process " << i + 1 << " with PID: " << pi.dwProcessId << endl;
    }

    // Record PIDs
    cout << "Recorded PIDs: ";
    for (const auto& pi : processInfos) {
        cout << pi.dwProcessId << " ";
    }
    cout << endl;

    // Wait for a few seconds before killing the processes
    Sleep(5000);

    // Kill the processes
    for (const auto& pi : processInfos) {
        if (TerminateProcess(pi.hProcess, 0)) {
            cout << "Killed process with PID: " << pi.dwProcessId << endl;
        } else {
            cerr << "Failed to kill process with PID: " << pi.dwProcessId << endl;
        }
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }

    return 0;
}
