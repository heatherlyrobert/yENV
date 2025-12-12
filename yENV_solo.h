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



/*········· ´················check· ´·········································*/
char        yenv_uexists            (char a_name [LEN_PATH]);
int         yenv_ulines             (char a_name [LEN_PATH]);
/*········· ´·················peek· ´·········································*/
char*       yenv_upeek              (char a_name [LEN_PATH], char a_dir);
char*       yenv_uindex             (char a_name [LEN_PATH], int n);
/*········· ´·············diagnose· ´·········································*/
char*       yenv_uwhich             (void);
int         yenv_uwhere             (void);
/*········· ´················debug· ´·········································*/
char        yenv_udebugging         (void);
char        yenv_uunit              (void);
char        yenv_unormal            (void);
char*       yenv_uprefix            (char a_dfile [LEN_TITLE], char a_dfunc [LEN_TITLE], int a_dline);
/*········· ´·················file· ´·········································*/
char        yenv_uopen_detail       (char a_dfile [LEN_TITLE], char a_dfunc [LEN_TITLE], int a_dline, char a_name [LEN_FULL], char a_mode, FILE **r_file);
char        yenv_uclose_detail      (char a_dfile [LEN_TITLE], char a_dfunc [LEN_TITLE], int a_dline, char a_name [LEN_FULL], FILE **r_file);
char        yenv_uopen              (char a_name [LEN_FULL], char a_mode, FILE **r_file);
char        yenv_uclose             (char a_name [LEN_FULL], FILE **r_file);
char        yenv_ucheck_stdin       (void);
char        yenv_upurge_stdin       (void);
char        yenv_uload_stdin        (char a_recd [LEN_RECD]);
char        yenv_uread              (FILE *a_file, short a_max, char r_recd [LEN_RECD], short *b_total, short *b_accept);
/*········· ´·················name· ´·········································*/
char        yenv_uname              (char a_dir [LEN_PATH], char a_file [LEN_PATH], char *r_style, char r_full [LEN_PATH]);
char        yenv_udetail            (char a_full [LEN_PATH], char *r_style, char r_dir [LEN_PATH], char r_file [LEN_FULL], char r_proj [LEN_LABEL], char r_base [LEN_HUND], char r_ext [LEN_TERSE], char *r_level, char *r_quality);
/*········· ´·················DONE· ´·········································*/



#endif
