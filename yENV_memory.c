/*===[[ START ]]==============================================================*/
#include    "yENV.h"
#include    "yENV_priv.h"


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
   DEBUG_YENV   yLOG_senter  (__FUNCTION__);
   if (a_terse != NULL)  DEBUG_YENV   yLOG_snote   (a_terse);
   /*---(check return)-------------------*/
   DEBUG_YENV   yLOG_spoint  (a_new);
   --rce;  if (a_new == NULL) {
      DEBUG_YENV   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV   yLOG_spoint  (*a_new);
   --rce;  if (a_force != 'y' && *a_new != NULL) {
      DEBUG_YENV   yLOG_snote   ("already set");
      DEBUG_YENV   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(default)------------------------*/
   *a_new = NULL;
   /*---(check size)---------------------*/
   DEBUG_YENV   yLOG_sint    (a_size);
   --rce;  if (a_size <= 0 || a_size >= MAX_BYTES) {
      DEBUG_YENV   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(allocate)-----------------------*/
   while (x_new == NULL) {
      ++x_tries;
      x_new = malloc (a_size);
      if (x_tries > 3)   break;
   }
   DEBUG_YENV   yLOG_sint    (x_tries);
   DEBUG_YENV   yLOG_spoint  (x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_YENV   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(wipe)---------------------------*/
   rc = 0;
   if (a_wiper != NULL)  rc = a_wiper (x_new);
   /*---(update counter)-----------------*/
   if (a_count != NULL)  ++(*a_count);
   /*---(save return)--------------------*/
   *a_new = x_new;
   /*---(complete)-----------------------*/
   DEBUG_YENV   yLOG_sexit   (__FUNCTION__);
   return rc;
}

char
yENV_free               (char *a_terse, void **a_old, int *a_count)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YENV   yLOG_senter  (__FUNCTION__);
   if (a_terse != NULL)  DEBUG_YENV   yLOG_snote   (a_terse);
   /*---(check return)-------------------*/
   DEBUG_YENV   yLOG_spoint  (a_old);
   --rce;  if (a_old == NULL) {
      DEBUG_YENV   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV   yLOG_spoint  (*a_old);
   --rce;  if (*a_old == NULL) {
      DEBUG_YENV   yLOG_snote   ("never set");
      DEBUG_YENV   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(clear and return)---------------*/
   free (*a_old);
   *a_old = NULL;
   /*---(update counter)-----------------*/
   if (a_count != NULL)  --(*a_count);
   /*---(complete)-----------------------*/
   DEBUG_YENV   yLOG_sexit   (__FUNCTION__);
   return 0;
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


