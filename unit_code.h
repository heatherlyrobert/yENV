

/*===[[ yENV_dir.c ]]=========================================================*/
/*········´ ´··············always·´ ´·········································*/
char        yENV__unit_quiet        (void);
char        yENV__unit_loud         (void);
char        yENV__unit_end          (void);
/*········´ ´············specific·´ ´·········································*/
char        yenv__dir_reset         (void);
char        yenv__dir_handler       (int a_read, int a_accept, int a_len, char a_name [LEN_HUND]);
char*       yenv__dir_show          (void);
char*       yENV_mime_unit          (char a_full [LEN_PATH], char a_type, char a_ltype, char a_prms);
/*········· ´·················DONE· ´·········································*/


