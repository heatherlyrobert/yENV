/*===[[ START ]]==============================================================*/
#include    "yENV.h"
#include    "yENV_priv.h"



/*===[[ GNU GENERAL PUBLIC LICENSE (GPL) ]]===================================*/
/*´´·········1·········2·········3·········4·········5·········6·········7·········8  */

#define  P_COPYRIGHT   \
   "copyright (c) 2020 robert.s.heatherly at balsashrike at gmail dot com"

#define  P_LICENSE     \
   "the only place you could have gotten this code is my github, my website,¦"   \
   "or illegal sharing. given that, you should be aware that this is GPL licensed."

#define  P_COPYLEFT    \
   "the GPL COPYLEFT REQUIREMENT means any modifications or derivative works¦"   \
   "must be released under the same GPL license, i.e, must be free and open."

#define  P_INCLUDE     \
   "the GPL DOCUMENTATION REQUIREMENT means that you must include the original¦" \
   "copyright notice and the full licence text with any resulting anything."

#define  P_AS_IS       \
   "the GPL NO WARRANTY CLAUSE means the software is provided without any¦"      \
   "warranty and the author cannot be held liable for damages."

#define  P_THEFT    \
   "if you knowingly violate the spirit of these ideas, i suspect you might "    \
   "find any number of freedom-minded hackers may take it quite personally ;)"

/*´´·········1·········2·········3·········4·········5·········6·········7·········8  */
/*===[[ GNU GENERAL PUBLIC LICENSE (GPL) ]]===================================*/



/*´´·········1·········2·········3·········4·········5·········6·········7·········8  */
#define  P_SUB_SCOPE   \
   "yENV_memory is focused on supporting unit testing wiping of memory allocated¦" \
   "structures.  it is very simple, but used somewhere in almost every programs¦"  \
   "unit testing.  i was tired of copying the code ;)"                     



#define    MAX_BYTES    20000

char
yENV_new                (char *a_terse, int a_size, void **a_new, int *a_count, char a_force, char *a_wiper (void *))
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   void       *x_new       = NULL;
   int         x_tries     =    0;
   /*---(header)-------------------------*/
   DEBUG_YENV   yLOG_enter   (__FUNCTION__);
   if (a_terse != NULL)  DEBUG_YENV   yLOG_note    (a_terse);
   /*---(check return)-------------------*/
   DEBUG_YENV   yLOG_point   ("a_new"     , a_new);
   --rce;  if (a_new == NULL) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV   yLOG_point   ("*a_new"    , *a_new);
   --rce;  if (a_force != 'y' && *a_new != NULL) {
      DEBUG_YENV   yLOG_note    ("already set");
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(default)------------------------*/
   *a_new = NULL;
   /*---(check size)---------------------*/
   DEBUG_YENV   yLOG_value   ("a_size"    , a_size);
   --rce;  if (a_size <= 0 || a_size >= MAX_BYTES) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(allocate)-----------------------*/
   while (x_new == NULL) {
      ++x_tries;
      x_new = malloc (a_size);
      if (x_tries > 3)   break;
   }
   DEBUG_YENV   yLOG_value   ("x_tries"   , x_tries);
   DEBUG_YENV   yLOG_spoint  (x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(wipe)---------------------------*/
   rc = 0;
   if (a_wiper != NULL)  rc = a_wiper (x_new);
   /*---(update counter)-----------------*/
   if (a_count != NULL)  ++(*a_count);
   /*---(save return)--------------------*/
   *a_new = x_new;
   DEBUG_YENV   yLOG_point   ("*a_new"    , *a_new);
   /*---(complete)-----------------------*/
   DEBUG_YENV   yLOG_exit    (__FUNCTION__);
   return rc;
}

char
yENV_free               (char *a_terse, void **a_old, int *a_count)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YENV   yLOG_enter   (__FUNCTION__);
   if (a_terse != NULL)  DEBUG_YENV   yLOG_note    (a_terse);
   /*---(check return)-------------------*/
   DEBUG_YENV   yLOG_point   ("a_old"     , a_old);
   --rce;  if (a_old == NULL) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV   yLOG_point   ("*a_old"    , *a_old);
   --rce;  if (*a_old == NULL) {
      DEBUG_YENV   yLOG_note    ("never set");
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(clear and return)---------------*/
   free (*a_old);
   *a_old = NULL;
   DEBUG_YENV   yLOG_point   ("*a_old"    , *a_old);
   /*---(update counter)-----------------*/
   if (a_count != NULL)  --(*a_count);
   /*---(complete)-----------------------*/
   DEBUG_YENV   yLOG_exit    (__FUNCTION__);
   return 1;
}

static char  s_memory  [LEN_FULL]  = "";

char
yENV_check_beg          (void)
{
   strlcpy  (s_memory, "[", LEN_FULL);
   return 0;
}

char
yENV_check_char         (char a_char)
{
   if      (a_char == '\0')       strlcat  (s_memory, "_", LEN_FULL);
   else if (a_char == '-')        strlcat  (s_memory, "_", LEN_FULL);
   else if (a_char == '?')        strlcat  (s_memory, "_", LEN_FULL);
   else                           strlcat  (s_memory, "X", LEN_FULL);
   return 0;
}

char
yENV_check_str          (char *a_str)
{
   if      (a_str == NULL)        strlcat  (s_memory, "_", LEN_FULL);
   else if (strlen (a_str) == 0)  strlcat  (s_memory, "_", LEN_FULL);
   else                           strlcat  (s_memory, "X", LEN_FULL);
   return 0;
}

char
yENV_check_ptr          (void *a_ptr)
{
   if      (a_ptr == NULL)        strlcat  (s_memory, "_", LEN_FULL);
   else                           strlcat  (s_memory, "X", LEN_FULL);
   return 0;
}

char
yENV_check_num          (int a_num)
{
   if      (a_num == 0)           strlcat  (s_memory, "_", LEN_FULL);
   else if (a_num == -1)          strlcat  (s_memory, "_", LEN_FULL);
   else                           strlcat  (s_memory, "X", LEN_FULL);
   return 0;
}

char
yENV_check_spacer       (void)
{
   strlcat  (s_memory, ".", LEN_FULL);
   return 0;
}

char
yENV_check_cat          (char *a_str)
{
   if      (a_str == NULL)        strlcat  (s_memory, "(BOOM)", LEN_FULL);
   else                           strlcat  (s_memory, a_str   , LEN_FULL);
   return 0;
}

char
yENV_check_end          (void)
{
   strlcat  (s_memory, "]", LEN_FULL);
   return 0;
}

char*
yENV_check              (void)
{
   return s_memory;
}


