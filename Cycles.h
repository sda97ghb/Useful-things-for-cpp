#ifndef CYCLES_H
#define CYCLES_H

#define repeat(__number_of_times) \
    for (unsigned __iteration_num = 0; \
         __iteration_num < (__number_of_times); \
         ++ __iteration_num)

#define forever \
    while (true)

#endif // CYCLES_H
