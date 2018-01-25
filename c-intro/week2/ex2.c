#include <stdio.h>

//A program that print out an Emacs commands list

int main()
{
  //Intro
  printf("\n========= Emacs Commands Tutor ==========\n");
  printf("========  Author : Ha Minh Duc  ==========\n\n");
  printf("Created as exercise of C Programming Introduction Course\n\n");

  printf("**Note: C stand for Ctrl and M stand for Meta\n");
  printf("       C-x means hold down Ctrl and type x\n\n\n");
  //Basic commands
  printf("1.BASIC COMMANDS:\n\n");
  printf("Find and open a file: C-x C-f 'filename'\n");
  printf("Delete: C-w\n");
  printf("Copy: M-w\n");
  printf("Paste: C-y\n");
  printf("Save: C-x C-s\n");
  printf("Save as: C-x C-w\n");
  printf("Exit Emacs: C-x C-c\n\n");
  //Moving around
  printf("2.MOVING AROUND:\n\n");
  printf("Move to the Top of the file: M-<\n");
  printf("Move to the End of the file: M->\n");
  printf("Next screen (page down): C-v\n");
  printf("Previous screen (page up): M-v\n");
  printf("Start of the current line: C-a\n");
  printf("End of the current line: C-e\n");
  printf("Go up line: C-p\n");
  printf("Go down line: C-n\n");
  printf("Forward one word: M-f\n");
  printf("Backward one word: M-b\n");
  printf("Go to a given line: M-x goto-line\n\n");
  //Another useful
  printf("3.ANOTHER USEFUL COMMANDS:\n\n");
  printf("Keyboard quit: C-g (stop a command which is taking too long)\n");
  printf("One window: C-x 1\n");
  printf("Splits the screen into two windows: C-x 2\n");
  printf("Move the cursor to the bottom window: C-x o\n");
  printf("Switch to buffer: C-x b\n");
  printf("Search a string: C-s\n");
  printf("Search backward: C-r\n");
  printf("Replace a string by anothe: M-%%r\n");
  printf("Open windows vertically: C-x 3\n");
  printf("Toggle read-only buffer mode: C-x C-q\n");
  printf("Kill buffer: C-x k\n");
  printf("Undo: C-x u\n\n");

  return 0;
}
