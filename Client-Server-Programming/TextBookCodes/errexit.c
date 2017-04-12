#include <stdarg.h>

#include <stdio.h>
#include <stdlib.h> //va_list valist, va_start(valist, num),va_arg(valist, int),va_end(valist)
                    //va_list argLst, va_start(argLst,format),vfprintf(stderr, format, argLst),va_end(argLst)

int errexit(const char *format,...){ //ellipses 
  va_list argsList;
  
  va_start(argsList,format);
  vfprintf(stderr,format,argsList);
  va_end(argsList);
  
  exit(0);
}
