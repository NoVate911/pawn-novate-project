/*      [ УСТАНОВКА НОВЫХ ЗНАЧЕНИЙ ]      */
/*      [ SETTING NEW VALUES ]      */
#undef MAX_PLAYER_NAME
    #define MAX_PLAYER_NAME         (24)
    #define MIN_PLAYER_NAME         (2)
#undef MAX_PLAYERS
    #define MAX_PLAYERS             (50)

/*      [ ИНФОРМАЦИЯ О СЕРВЕРЕ ]      */
/*      [ SERVER INFORMATION ]      */
#define SERVER_NAME                 "NoVate Project"
#define SERVER_AUTHOR               "NoVate Source"
#define SERVER_VERSION              "build 15039"
#define SERVER_TYPE                 "RolePlay"

/*      [ ШАБЛОН ДЛЯ ВЫВОДА ]      */
/*      [ TEMPLATES FOR OUTPUT ]      */
#define DEBUG_MYSQL                 "[MySQL] |"
#define DEBUG_LOAD                  "[LOAD] |"
#define DEBUG_INFO                  "[INFO] |"

/*      [ ПЕРЕМЕННЫЕ ФУНКЦИЙ ]      */
/*      [ FUNCTION VARIABLES ]      */
#define function%0(%1)              forward%0(%1); public%0(%1)
#define dCreate:%0(%1)              DialogCreate:%0(%1)
#define dResponse:%0(%1)            DialogResponse:%0(%1, response, listitem, inputtext[])
#define randomEx(%1, %2)            (random(%2 - %1) + %1)
#define SCM                         SendClientMessage
#define SCMTA                       SendClientMessageToAll
#define SPD                         ShowPlayerDialog
#define SCMf                        SendClientMessagef
#define SCMTAf                      SendClientMessageToAllf