/*============================[[    beg-code    ]]============================*/
#ifndef   YENV_SOLO   
#define   YENV_SOLO         loaded

#include  <ySTR_solo.h>


int         yENV_ulines             (char a_name [LEN_PATH]);

char*       yENV_upeek              (char a_name [LEN_PATH], char a_dir);
char*       yENV_uindex             (char a_name [LEN_PATH], int n);

char*       yENV_uwhich             (void);
int         yENV_uwhere             (void);

char        yenv_uunit              (void);
char        yenv_unormal            (void);


#endif
