/*
 *  AUTHOR: Sven Goldt (goldt@math.tu-berlin.de)
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
*/


#include <string.h>

static struct s_notes
{
 float frequency;
 char name[4];
} notes[] = {
16.4 , "c-0", 17.3 , "c#0", 18.4 , "d-0", 19.4 , "d#0",
20.6 , "e-0", 21.8 , "f-0", 23.1 , "f#0", 24.5 , "g-0",
26.0 , "g#0", 27.5 , "a-0", 29.1 , "a#0", 30.9 , "h-0",

32.7 , "c-1", 34.6 , "c#1", 36.7 , "d-1", 38.9 , "d#1",
41.2 , "e-1", 43.7 , "f-1", 46.2 , "f#1", 49.0 , "g-1",
51.9 , "g#1", 55.0 , "a-1", 58.3 , "a#1", 61.7 , "h-1",

65.4 , "c-2", 69.3 , "c#2", 73.4 , "d-2", 77.8 , "d#2",
82.4 , "e-2", 87.3 , "f-2", 92.5 , "f#2", 98.0 , "g-2",
103.8, "g#2", 110.0, "a-2", 116.5, "a#2", 123.5, "h-2",

130.8, "c-3", 138.6, "c#3", 146.8, "d-3", 155.6, "d#3",
164.8, "e-3", 174.6, "f-3", 185.0, "f#3", 196.0, "g-3",
207.7, "g#3", 220.0, "a-3", 233.1, "a#3", 246.9, "h-3",

261.6, "c-4", 277.2, "c#4", 293.7, "d-4", 311.1, "d#4",
329.6, "e-4", 349.2, "f-4", 370.0, "f#4", 392.0, "g-4",
415.3, "g#4", 440.0, "a-4", 466.2, "a#4", 493.9, "h-4",

523.3, "c-5", 554.4, "c#5", 587.3, "d-5", 622.3, "d#5",
659.3, "e-5", 698.5, "f-5", 740.0, "f#5", 784.0, "g-5",
830.6, "g#5", 880.0, "a-5", 932.3, "a#5", 987.8, "h-5",

1046.5, "c-6", 1108.7, "c#6", 1174.7, "d-6", 1244.5, "d#6",
1318.5, "e-6", 1396.6, "f-6", 1480.0, "f#6", 1568.0, "g-6",
1661.2, "g#6", 1760.0, "a-6", 1864.7, "a#6", 1975.5, "h-6",

2093.0, "c-7", 2217.5, "c#7", 2349.3, "d-7", 2489.0, "d#7",
2637.0, "e-7", 2793.8, "f-7", 2960.0, "f#7", 3136.0, "g-7",
3322.4, "g#7", 3520.0, "a-7", 3729.3, "a#7", 0.0 , "0",
};

float name_to_val(char *tune)
{
struct s_notes *ptr;

 for (ptr=notes; ptr->frequency !=0; ptr++)
  if (strncmp(tune,ptr->name,3) == 0) return(ptr->frequency);

return(0.0);
}

char *val_to_name(float frequency)
{
struct s_notes *ptr;

 for (ptr=notes; ptr->frequency !=0; ptr++)
  if (ptr->frequency == frequency) return(ptr->name);

return(NULL);
}
