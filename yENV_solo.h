/*============================[[    beg-code    ]]============================*/
#ifndef   YENV_SOLO   
#define   YENV_SOLO         loaded

#include  <ySTR_solo.h>


char        yenv_uexists            (char a_name [LEN_PATH]);
int         yenv_ulines             (char a_name [LEN_PATH]);

char*       yenv_upeek              (char a_name [LEN_PATH], char a_dir);
char*       yenv_uindex             (char a_name [LEN_PATH], int n);

char*       yenv_uwhich             (void);
int         yenv_uwhere             (void);

char        yenv_uunit              (void);
char        yenv_unormal            (void);


#endif
