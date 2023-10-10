#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>


void print_command_prompt(){
  printf("myShell>");
}

char* read_and_save_command(){
  char temp_command[256];
  char* command = (char*)malloc(256 + 5);
  if(command == NULL){
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  scanf("%255s", temp_command);
  sprintf(command, "/bin/%s", temp_command);
  return command;
}

int main(void){
  while(1){
    print_command_prompt();
    char* command = read_and_save_command();

  //Elternprozess
    if (fork() > 0){
      int status;
      wait(&status);
    }
  //Kindprozess
    else{
      char *argv[] = {command, NULL};
      char *envp[] = {NULL};
      errno = 0;
      if (execve(command, argv, envp) == -1){
        perror("execve");
        exit(EXIT_FAILURE);
      }
    }
    free(command);
  }
  return 0;
}
