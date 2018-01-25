#include <stdio.h>

/* A program that calculate circumference, area and volume
of a square (and cube) with the given edge */

int main()
{
  unsigned int edge, cir, s_area, c_area, vol;
  edge = 10;  //given

  //logic part
  cir = 4 * edge;
  s_area = edge * edge;
  c_area = s_area * 6;
  vol = s_area * edge;

  //display part
  printf("Square's edge = %d\n", edge);
  printf("Square's circumference = %d\n", cir);
  printf("Square's area = %d\n", s_area);
  printf("Cube's area = %d\n", c_area);
  printf("Cube's volume = %d\n", vol);
  
  return 0;
}
