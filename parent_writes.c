#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
int main() {
    int fd[2];
    pid_t pid;
    char message[] = "Hello from parent";
    char buffer[100];
    if (pipe(fd) == -1) {
        perror("Pipe failed");
        return 1;
    }
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        close(fd[1]);
        read(fd[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);
        close(fd[0]);
    } else {
        close(fd[0]);
        write(fd[1], message, strlen(message) + 1);
        close(fd[1]);
    }
    return 0;
}
