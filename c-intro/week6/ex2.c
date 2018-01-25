#include <stdio.h>

//transforms a compass heading to a compass bearing

int main()
{
  float h;
  printf("Enter compass heading (0 - 360): ");
  scanf("%f", &h);

  if(h == 0 || h == 360)
    printf("North\n");
  else if(0 < h && h < 90)
    printf("North east\n");
  else if(h == 90)
    printf("East\n");
  else if(90 < h && h < 180)
    printf("South east\n");
  else if(h == 180)
    printf("South\n");
  else if(180 < h && h < 270)
    printf("South west\n");
  else if(h == 270)
    printf("West\n");
  else if(270 < h && h < 360)
    printf("North west\n");
  else
    printf("Wrong value\n");

  return 0;
}
