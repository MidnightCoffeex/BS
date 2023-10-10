


...
while(1) {
  print_command_promt();
  read_and_save_command();

  if(fork() > 0) {
    /* parent process */
    wait(status);
  }
  else {
    /* child process */
    execve(command, ...);
  }
}
...