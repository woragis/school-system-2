#ifndef USER_H
#define USER_H

#define USER_NAME_LENGTH 50
#define USER_RGM_LENGTH 10

typedef struct user
{
    char name[USER_NAME_LENGTH];
    char rgm[USER_RGM_LENGTH];
} user_t;

#endif
