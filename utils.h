#ifndef UTILS_H
#define UTILS_H

#define SPLITERATE(str,split,p) for (const char *p = strtok(str, split); p != NULL; p = strtok(NULL, split))

#endif //UTILS_H
