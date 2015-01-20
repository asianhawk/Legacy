#ifndef _INPUT_H
#define _INPUT_H

extern int readChar (int filedes, char *c);
extern int readLine(int filedes, char *line, int maxlen);
extern int inputTimeout(int filedes, unsigned int milliseconds);
extern ssize_t readAll(int fd, void * data, size_t count);

#endif /* _INPUT_H */
