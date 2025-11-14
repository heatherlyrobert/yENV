/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef YENV_HGUARD
#define YENV_HGUARD loaded



#include    <stdio.h>        /* C_ANSI : strcpy, strlen, strchr, strcmp, ...  */
#include    <ySTR_solo.h>



/*---(standard recturn codes)-------------------*/
#define     RC_ACK          0
#define     RC_POSITIVE     1
#define     RC_OVERRIDE     2
#define     RC_REPAIR       3
#define     RC_WARNING      4
#define     RC_FAILED       5
#define     RC_FATAL        5   /* depricated */
/*---(c_type)-------------------------*/
#define     YENV_BLOCK       'b'
#define     YENV_CHAR        'c'
#define     YENV_DIR         'd'
#define     YENV_HARD        'h'
#define     YENV_IPSOC       'i'
#define     YENV_PIPE        'p'
#define     YENV_REG         'r'
#define     YENV_SYM         's'
#define     YENV_NONE        '-'
#define     YENV_WTF         '?'
#define     YENV_ANY         '!'
/*---(defense)------------------------*/
#define     YENV_REAL        "bcdhiprs"
#define     YENV_TYPES       "bcdhiprs-"
/*---(c_style)------------------------*/
#define     YENV_BOTH        'b'
/*---(c_naming)-----------------------*/
#define     YENV_WILD        '-'
#define     YENV_NORMAL      'n'
#define     YENV_STANDARD    's'
#define     YENV_LOCAL       'l'
#define     YENV_CENTRAL     'c'
/*---(defense)------------------------*/
#define     YENV_NAMING      "-nslc"
/*---(c_flag)-------------------------*/
#define     YENV_FIX         'f'
#define     YENV_FORCE       'F'
#define     YENV_HAMMER      '!'
/*---(done)---------------------------*/

#define     YENV_QUALITY     'y'
#define     YENV_TOOSHORT    '<'
#define     YENV_TOOLONG     '>'
#define     YENV_BADCHAR     '#'

#define     YENV_LOGIN       'y'
#define     YENV_NOLOGIN     '·'

#define     YENV_ACTIVE      'y'
#define     YENV_LOCKED      '!'
#define     YENV_UNSET       '*'
#define     YENV_NOPASS      '?'



/*===[[ yENV_base.c ]]========================================================*/
/*········· ´······················ ´·········································*/
char*       yENV_version            (void);
char        yENV_whoami             (int *r_pid, int *r_ppid, int *r_uid, int *r_euid, char *r_root, char r_user [LEN_USER], char a_wheel, int *r_gid, int *r_egid, char r_group [LEN_USER]);
char        yENV_project            (char r_whoami [LEN_LABEL]);
/*········· ´······················ ´·········································*/



/*===[[ yENV_peek.c ]]========================================================*/
/*········· ´······················ ´·········································*/
/*---(content)--------------*/
char*       yENV_peekier            (char a_style, char a_name [LEN_PATH], char a_dir, int n, int *a_count);
/*---(simplifiers)----------*/
char*       yENV_peek               (char a_name [LEN_PATH], char a_dir);
char*       yENV_index              (char a_name [LEN_PATH], int n);
char*       yENV_peek_vis           (char a_name [LEN_PATH], int n);
char*       yENV_peek_field         (char a_name [LEN_PATH], int n);
int         yENV_lines              (char a_name [LEN_PATH]);
char        yENV_reset              (char a_name [LEN_PATH]);
/*---(debugging)------------*/
char*       yENV_where              (void);
int         yENV_which              (void);
/*---(comparision)----------*/
char        yENV_diff               (char *a_actual, char *a_expect);
/*········· ´······················ ´·········································*/



/*===[[ yENV_user.c ]]========================================================*/
/*········· ´······················ ´·········································*/
/*---(driver)---------------*/   /*--- DEPRICATED ----------------------------*/
char        yENV_user_data          (char a_type, char b_name [LEN_USER], int *b_uid, int *r_gid, char r_home [LEN_HUND], char r_shell [LEN_HUND], char *r_quality, char *r_active, char *r_login, char *r_ngroup, char r_gnames [LEN_HUND], char r_gids [LEN_HUND]);
char        yENV_user_full          (char a_type, char a_text [LEN_USER], char r_name [LEN_USER], int *r_uid, int *r_gid, char r_home [LEN_HUND], char r_shell [LEN_HUND], char r_handle [LEN_LABEL], char *r_naming, char *r_active, char *r_login, char *r_ngroup, char r_gnames [LEN_HUND], char r_gids [LEN_HUND]);
/*---(simplifiers)----------*/
char        yENV_user               (char a_text [LEN_USER], char r_name [LEN_USER], int *r_uid);
char        yENV_user_uid           (char a_type, int a_value, char r_name [LEN_USER], int *r_uid);
char        yENV_user_basics        (char a_text [LEN_USER], int *r_uid, int *r_gid, char r_home [LEN_HUND], char r_shell [LEN_HUND]);
/*---(unit-testing)---------*/
char        yENV_user_add           (char a_name [LEN_USER], int a_uid, char a_home, char a_shell);
char        yENV_user_del           (char a_name [LEN_USER]);
char        yENV_user_purge         (void);
char        yENV_user_switch        (char a_name [LEN_USER]);
/*---(access)---------------*/
int         yENV_user_count         (void);
char*       yENV_user_by_cursor     (char a_dir);
char*       yENV_user_by_text       (char a_text [LEN_USER]);
/*---(done)-----------------*/



/*===[[ yENV_group.c ]]=======================================================*/
/*········· ´······················ ´·········································*/
/*---(driver)---------------*/   /*--- DEPRICATED ----------------------------*/
char        yENV_group_data         (char a_type, char b_name [LEN_USER], int *b_gid, char *r_quality, char *r_active, char *r_nuser, char r_unames [LEN_HUND], char r_uids [LEN_HUND]);
char        yENV_group_full         (char a_type, char a_text [LEN_USER], char r_name [LEN_USER], int *r_gid, char r_handle [LEN_LABEL], char *r_quality, char *r_active, char *r_nuser, char r_unames [LEN_HUND], char r_uids [LEN_HUND]);
/*---(simplifiers)----------*/
char        yENV_group              (char a_text [LEN_USER], char r_name [LEN_USER], int *r_gid);
char        yENV_group_gid          (char a_type, int a_value, char r_name [LEN_USER], int *r_gid);
/*---(data-access)----------*/
int         yENV_group_count        (void);
char*       yENV_group_by_cursor    (char a_dir);
char*       yENV_group_by_text      (char a_text [LEN_USER]);
/*---(unit-testing)---------*/
char        yENV_group_add          (char a_name [LEN_USER], int a_gid);
char        yENV_group_del          (char a_name [LEN_USER]);
char        yENV_group_purge        (void);
char        yENV_group_switch       (char a_name [LEN_USER]);
/*---(driver)---------------*/



/*===[[ yENV_perms.c ]]=======================================================*/
/*········· ´······················ ´·········································*/
/*---(driver)---------------*/   /*--- DEPRICATED ----------------------------*/
char        yENV_perms_data         (char a_type, char b_name [LEN_TERSE], int *b_perms, char b_disp [LEN_TERSE]);
/*---(current)--------------*/
char        yENV_perms_full         (char a_type, char a_text [LEN_TERSE], char r_name [LEN_TERSE], int *r_perms, char r_disp [LEN_TERSE], char r_desc [LEN_TITLE], char r_handle [LEN_LABEL]);
/*---(simplifiers)----------*/
char        yENV_perms              (char a_text [LEN_TERSE], char r_name [LEN_TERSE], int *r_prm, char r_disp [LEN_TERSE], char r_desc [LEN_HUND]);
char        yENV_perms_octal        (char a_type, int a_value, char r_name [LEN_TERSE], int *r_prm, char r_disp [LEN_TERSE]);
/*---(access)---------------*/
int         yENV_perms_count        (void);
char*       yENV_perms_by_cursor    (char a_dir);
char*       yENV_perms_by_text      (char a_text [LEN_TERSE]);
/*········· ´·················DONE· ´·········································*/



/*===[[ yENV_entry.c ]]=======================================================*/
/*········· ´······················ ´·········································*/
/*---(create)---------------*/
char        yENV_create             (char a_type, char a_name [LEN_PATH], int a_uid, int a_gid, int a_prm, int a_major, int a_minor, char a_link [LEN_PATH]);
char        yENV_hash               (char a_type, char a_name [LEN_PATH], char r_hash [LEN_DESC]);
char        yENV_touchier           (char a_type, char a_name [LEN_PATH], char a_owner [LEN_USER], char a_group [LEN_USER], char a_perms [LEN_TERSE], int a_major, int a_minor, char a_link [LEN_PATH], char a_modified);
char        yENV_touch              (char a_name [LEN_PATH], char a_owner [LEN_USER], char a_group [LEN_USER], char a_perms [LEN_TERSE]);
char        yENV_mkdir              (char a_name [LEN_PATH], char a_owner [LEN_USER], char a_group [LEN_USER], char a_perms [LEN_TERSE]);
char        yENV_modified           (char a_name [LEN_PATH]);
/*---(remove)---------------*/
char        yENV_removier           (char a_type, char a_name [LEN_PATH]);
char        yENV_rm                 (char a_name [LEN_PATH]);
char        yENV_rmdir              (char a_name [LEN_PATH]);
char        yENV_rmdir_fully        (char a_name [LEN_PATH]);
/*---(checking)-------------*/
char        yENV_exists             (char a_name [LEN_PATH]);
char        yENV_size               (char a_name [LEN_PATH], long *r_bytes);
char*       yENV_typedesc           (char a_type);
char        yENV_detail             (char a_name [LEN_PATH], char r_tdesc [LEN_TERSE], int *r_uid, char r_owner [LEN_USER], int *r_gid, char r_group [LEN_USER], int *r_prm, char r_perms [LEN_TERSE], char r_pdisp [LEN_TERSE], long *r_bytes, int *r_epoch, int *r_major, int *r_minor, char r_link [LEN_PATH], int *r_dev, int *r_inode, char r_hash [LEN_DESC]);
char*       yENV_detail_unit        (char a_name [LEN_PATH]);
/*········· ´·················DONE· ´·········································*/



/*===[[ yENV_name.c ]]========================================================*/
/*········· ´······················ ´·········································*/
char        yENV_name_full          (char a_dir [LEN_PATH], char a_file [LEN_PATH], char *r_style, char r_full [LEN_PATH]);
char        yENV_name_split         (char a_full [LEN_PATH], char *r_style, char r_dir [LEN_PATH], char r_file [LEN_PATH]);
char        yENV_name_detail        (char a_full [LEN_PATH], char *r_style, char r_dir [LEN_PATH], char r_file [LEN_FULL], char r_proj [LEN_LABEL], char r_base [LEN_HUND], char r_ext [LEN_TERSE], char *r_level, char *r_quality);
/*········· ´·················DONE· ´·········································*/



/*===[[ yENV_file.c ]]========================================================*/
/*········· ´······················ ´·········································*/
char        yENV_open_full          (char a_label [LEN_LABEL], char c_force, char a_dir [LEN_PATH], char a_file [LEN_PATH], char a_mode, char r_mode [LEN_SHORT], char r_note [LEN_LABEL], char r_full [LEN_PATH], FILE **b_file);
char        yENV_open               (char a_dir [LEN_PATH], char a_file [LEN_PATH], char a_mode, FILE **b_file);
char        yENV_close_full         (char a_label [LEN_LABEL], FILE **b_file, char c_sync);
char        yENV_close              (FILE **b_file);
char        yENV_read               (FILE *a_file, char c_comment, char c_visible, int *b_read, int *b_accept, char b_curr [LEN_RECD], char r_prev [LEN_RECD]);
/*········· ´·················DONE· ´·········································*/



/*===[[ yENV_memory.c ]]======================================================*/
/*········· ´················alloc· ´·········································*/
char        yENV_new                (char *a_terse, int a_size, void **a_new, int *a_count, char a_force, char *a_wiper (void *));
char        yENV_free               (char *a_terse, void **a_old, int *a_count);
/*········· ´·················unit· ´·········································*/
char        yENV_check_beg          (void);
char        yENV_check_char         (char a_char);
char        yENV_check_str          (char *a_str);
char        yENV_check_ptr          (void *a_ptr);
char        yENV_check_num          (int a_num);
char        yENV_check_spacer       (void);
char        yENV_check_cat          (char *a_str);
char        yENV_check_end          (void);
char*       yENV_check              (void);
/*········· ´·················DONE· ´·········································*/



#endif
/*===[[ END ]]================================================================*/
