/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef YENV_HGUARD
#define YENV_HGUARD loaded



#include    <stdio.h>        /* C_ANSI : strcpy, strlen, strchr, strcmp, ...  */
#include <ySTR_solo.h>



/*---(standard recturn codes)-------------------*/
#define     RC_ACK          0
#define     RC_POSITIVE     1
#define     RC_OVERRIDE     2
#define     RC_REPAIR       3
#define     RC_WARNING      4
#define     RC_FAILED       5

#define     RC_FATAL        5   /* depricated */



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

#define     YENV_REAL        "bcdhiprs"
#define     YENV_TYPES       "bcdhiprs-"



/*===[[ yENV_base.c ]]========================================================*/
/*иииииииии ┤ииииииииииииииииииииии ┤иииииииииииииииииииииииииииииииииииииииии*/
char*       yENV_version            (void);
/*---(done)-----------------*/



/*===[[ koios_self.c ]]=======================================================*/
/*иииииииии ┤ииииииииииииииииииииии ┤иииииииииииииииииииииииииииииииииииииииии*/
/*---(myself)---------------*/
/*> char        yENV_whoami             (int *r_pid, int *r_ppid, int *r_uid, int *r_euid, char *r_root, char r_user [LEN_USER], char a_wheel, int *r_gid, int *r_egid, char r_group [LEN_USER]);   <*/
/*---(done)-----------------*/



/*===[[ yENV_peek.c ]]========================================================*/
/*иииииииии ┤ииииииииииииииииииииии ┤иииииииииииииииииииииииииииииииииииииииии*/
/*---(content)--------------*/
char*       yENV_peekier            (char a_style, char a_name [LEN_PATH], int n, int *a_count);
char*       yENV_peek               (char a_name [LEN_PATH], int n);
char*       yENV_peek_vis           (char a_name [LEN_PATH], int n);
char*       yENV_peek_field         (char a_name [LEN_PATH], int n);
int         yENV_lines              (char a_name [LEN_PATH]);
/*---(comparision)----------*/
char        yENV_diff               (char *a_actual, char *a_expect);
/*---(done)-----------------*/



/*===[[ yENV_user.c ]]========================================================*/
/*иииииииии ┤ииииииииииииииииииииии ┤иииииииииииииииииииииииииииииииииииииииии*/
/*---(driver)---------------*/   /*--- DEPRICATED ----------------------------*/
char        yENV_user_data          (char a_type, char b_name [LEN_USER], int *b_uid, int *r_gid, char r_dir [LEN_HUND], char r_shell [LEN_HUND]);
/*---(flexible)-------------*/
char        yENV_user_full          (char a_type, char a_text [LEN_USER], char r_name [LEN_USER], int *r_uid, int *r_gid, char r_dir [LEN_HUND], char r_shell [LEN_HUND], char r_handle [LEN_LABEL]);
/*---(simplifiers)----------*/
char        yENV_user               (char a_text [LEN_USER], char r_name [LEN_USER], int *r_uid);
char        yENV_user_uid           (char a_type, int a_value, char r_name [LEN_USER], int *r_uid);
/*---(unit-testing)---------*/
char        yENV_user_add           (char a_name [LEN_USER], int a_uid, char a_home, char a_shell);
char        yENV_user_del           (char a_name [LEN_USER]);
char        yENV_user_purge         (void);
char        yENV_user_switch        (char a_name [LEN_USER]);
/*---(done)-----------------*/



/*===[[ yENV_group.c ]]=======================================================*/
/*иииииииии ┤ииииииииииииииииииииии ┤иииииииииииииииииииииииииииииииииииииииии*/
/*---(driver)---------------*/   /*--- DEPRICATED ----------------------------*/
char        yENV_group_data         (char a_type, char b_name [LEN_USER], int *b_gid);
/*---(current)--------------*/
char        yENV_group_full         (char a_type, char a_text [LEN_USER], char r_name [LEN_USER], int *r_gid, char r_handle [LEN_LABEL]);
/*---(simplifiers)----------*/
char        yENV_group              (char a_text [LEN_USER], char r_name [LEN_USER], int *r_gid);
char        yENV_group_gid          (char a_type, int a_value, char r_name [LEN_USER], int *r_gid);
/*---(unit-testing)---------*/
char        yENV_group_add          (char a_name [LEN_USER], int a_gid);
char        yENV_group_del          (char a_name [LEN_USER]);
char        yENV_group_purge        (void);
char        yENV_group_switch       (char a_name [LEN_USER]);
/*---(driver)---------------*/



/*===[[ yENV_perms.c ]]=======================================================*/
/*иииииииии ┤ииииииииииииииииииииии ┤иииииииииииииииииииииииииииииииииииииииии*/
/*---(driver)---------------*/   /*--- DEPRICATED ----------------------------*/
char        yENV_perms_data         (char a_type, char b_name [LEN_TERSE], int *b_perms, char b_disp [LEN_TERSE]);
/*---(current)--------------*/
char        yENV_perms_full         (char a_type, char a_text [LEN_TERSE], char r_name [LEN_TERSE], int *r_perms, char r_disp [LEN_TERSE], char r_desc [LEN_HUND], char r_handle [LEN_LABEL]);
/*---(simplifiers)----------*/
char        yENV_perms              (char a_text [LEN_TERSE], char r_name [LEN_TERSE], int *r_prm, char r_disp [LEN_TERSE], char r_desc [LEN_HUND]);
char        yENV_perms_octal        (char a_type, int a_value, char r_name [LEN_TERSE], int *r_prm, char r_disp [LEN_TERSE]);
/*---(done)-----------------*/



/*===[[ yENV_entry.c ]]=======================================================*/
/*иииииииии ┤ииииииииииииииииииииии ┤иииииииииииииииииииииииииииииииииииииииии*/
/*---(create)---------------*/
char        yENV_create             (char a_type, char a_name [LEN_PATH], int a_uid, int a_gid, int a_prm, int a_major, int a_minor, char a_link [LEN_PATH]);
char        yENV_hash               (char a_type, char a_name [LEN_PATH], char r_hash [LEN_DESC]);
char        yENV_touchier           (char a_type, char a_name [LEN_PATH], char a_owner [LEN_USER], char a_group [LEN_USER], char a_perms [LEN_TERSE], int a_major, int a_minor, char a_link [LEN_PATH]);
char        yENV_touch              (char a_name [LEN_PATH], char a_own [LEN_USER], char a_group [LEN_USER], char a_perms [LEN_TERSE]);
char        yENV_mkdir              (char a_name [LEN_PATH], char a_own [LEN_USER], char a_group [LEN_USER], char a_perms [LEN_TERSE]);
/*---(remove)---------------*/
char        yENV_removier           (char a_type, char a_name [LEN_PATH]);
char        yENV_rm                 (char a_name [LEN_PATH]);
char        yENV_rmdir              (char a_name [LEN_PATH]);
/*---(checking)-------------*/
char        yENV_exists             (char a_name [LEN_PATH]);
char*       yENV_typedesc           (char a_type);
char        yENV_detail             (char a_name [LEN_PATH], char r_tdesc [LEN_TERSE], int *r_uid, char r_owner [LEN_USER], int *r_gid, char r_group [LEN_USER], int *r_prm, char r_perms [LEN_TERSE], char r_pdisp [LEN_TERSE], long *r_bytes, int *r_epoch, int *r_major, int *r_minor, char r_link [LEN_PATH], int *r_dev, int *r_inode, char r_hash [LEN_DESC]);
char*       yENV_detail_unit        (char a_name [LEN_PATH]);
/*---(done)-----------------*/



/*===[[ yENV_audit.c ]]=======================================================*/
/*иииииииии ┤ииииииииииииииииииииии ┤иииииииииииииииииииииииииииииииииииииииии*/
char        yENV_audit              (char a_type, char c_flag, char a_dir [LEN_PATH], char a_file [LEN_LABEL], char a_owner [LEN_USER], char a_group [LEN_USER], char a_perms [LEN_TERSE], int a_major, int a_minor, char a_ttype, char a_target [LEN_PATH]);
char        yENV_score_def          (void);
char*       yENV_score              (void);
/*---(simplifiers)----------*/
char        yENV_audit_del          (char c_flag, char a_dir [LEN_PATH], char a_file [LEN_LABEL]);
char        yENV_audit_reg          (char c_flag, char a_dir [LEN_PATH], char a_file [LEN_LABEL], char a_owner [LEN_USER], char a_group [LEN_USER], char a_perms [LEN_TERSE]);
/*---(done)-----------------*/



/*===[[ koios_file.c ]]=======================================================*/
/*иииииииии ┤ииииииииииииииииииииии ┤иииииииииииииииииииииииииииииииииииииииии*/
/*---(openning)-------------*/
char        yENV_open_full          (char a_dir [LEN_PATH], char a_file [LEN_LABEL], char a_mode, FILE **r_file, char c_check, char c_force, char c_fix, char a_owner [LEN_USER], char a_group [LEN_USER], char a_perms [LEN_TERSE]);
char        yENV_open               (char a_dir [LEN_PATH], char a_file [LEN_LABEL], char a_mode, FILE **r_file);
char        yENV_open_safe          (char a_dir [LEN_PATH], char a_file [LEN_LABEL], char a_mode, FILE **r_file, char a_owner [LEN_USER], char a_group [LEN_USER], char a_perms [LEN_TERSE]);
char        yENV_open_fix           (char a_dir [LEN_PATH], char a_file [LEN_LABEL], char a_mode, FILE **r_file, char a_owner [LEN_USER], char a_group [LEN_USER], char a_perms [LEN_TERSE]);
char        yENV_open_force         (char a_dir [LEN_PATH], char a_file [LEN_LABEL], char a_mode, FILE **r_file, char a_owner [LEN_USER], char a_group [LEN_USER], char a_perms [LEN_TERSE]);
/*---(closing)--------------*/
char        yENV_close_full         (char a_dir [LEN_PATH], char a_file [LEN_PATH], char a_mode, FILE **b_file, char c_check);
char        yENV_close              (FILE **b_file);
/*---(done)-----------------*/



#endif
/*===[[ END ]]================================================================*/
