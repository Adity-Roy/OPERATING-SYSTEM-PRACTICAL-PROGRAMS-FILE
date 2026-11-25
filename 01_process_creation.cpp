#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
using namespace std;

int main() {
    cout << "Parent process: PID = " << getpid() << endl;
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        cout << "Child process: PID = " << getpid() << ", Parent PID = " << getppid() << endl;
        cout << "Child is about to execute ls -l" << endl;
        execlp("ls", "ls", "-l", (char *)NULL);
        perror("exec failed");
        _exit(1);
    } else {
        int status;
        cout << "Parent waiting for child (PID = " << pid << ") to finish..." << endl;
        wait(&status);
        if (WIFEXITED(status))
            cout << "Child exited with status " << WEXITSTATUS(status) << endl;
        cout << "Parent process resumes and exits." << endl;
    }
    return 0;
}