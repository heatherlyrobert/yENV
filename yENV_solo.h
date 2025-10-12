/*============================[[    beg-code    ]]============================*/
#ifndef   YENV_SOLO   
#define   YENV_SOLO         loaded



#include    <stdio.h>
#include    <stdarg.h>                   /* va_arg                              */
#include    <string.h>
#include    <unistd.h>                   /* unlink                              */
#include    <sys/stat.h>          /* fstat, umask                                */
#include    <fcntl.h>
#include    <errno.h>             /* allow use of errno value                 */

#include    <ySTR_solo.h>
#include    <yDLST_solo.h>
#include    <yLOG.h>         /* CUSTOM : heatherly debugging framework        */
#include    <yURG.h>



/*········· ´······················ ´·········································*/
char        yenv_uexists            (char a_name [LEN_PATH]);
int         yenv_ulines             (char a_name [LEN_PATH]);
/*········· ´······················ ´·········································*/
char*       yenv_upeek              (char a_name [LEN_PATH], char a_dir);
char*       yenv_uindex             (char a_name [LEN_PATH], int n);
/*········· ´······················ ´·········································*/
char*       yenv_uwhich             (void);
int         yenv_uwhere             (void);
/*········· ´······················ ´·········································*/
char        yenv_uunit              (void);
char        yenv_unormal            (void);
/*········· ´······················ ´·········································*/
char        yenv_uopen              (char a_name [LEN_HUND], char a_mode, FILE **r_file);
char        yenv_uclose             (FILE **r_file);
char        yenv_ucheck_stdin       (void);
char        yenv_upurge_stdin       (void);
char        yenv_uload_stdin        (char a_recd [LEN_RECD]);
char        yenv_uread              (FILE *a_file, short a_max, char r_recd [LEN_RECD], short *b_total, short *b_accept);
/*········· ´······················ ´·········································*/



#endif
