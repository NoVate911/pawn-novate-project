/*

[ ============================== ]
   �������� ����� �������� ����
  READ BEFORE LAUNCHING THE MOD
[ ============================== ]

-- [ RUS ] --
������ ������ ���� �������� ������� �������������.
��������� ����������� ����� ����� ������������ � �������� ��� �� ����� �� ����� ��������.

-- [ ENG ] --
This build was written by a Russian developer.
Some translated text may be displayed with errors or will not be translated at all.

*/

main(){}

/*      [ ����������� ���������(��������) ]      */
/*      [ CONNECTING LIBRARIES (INCLUDS) ]      */
#include <a_samp>
#include "../include/a_mysql.inc"
#include "../include/md5.inc"
#include "../include/sscanf2.inc"
#include "../include/Pawn.CMD.inc"
#include "../include/Pawn.Regex.inc"
#include "../include/streamer.inc"
#include "../include/YSF.inc"
#include "../include/mdialog.inc"

/*      [ �������������� ������� � ������� ]      */
/*      [ ADDITIONAL FUNCTIONS AND CONFIGS ]      */
#include "./src/config.inc"
#include "./src/utils.inc"

/*      [ ��������� ������� ]      */
/*      [ SERVER SIDE ]      */
#include "./src/server/OnGameModeInit.inc"
#include "./src/server/OnGameModeExit.inc"

/*      [ ���������� ������� ]      */
/*      [ CLIENT SIDE ]      */
#include "./src/player/OnPlayerConnect.inc"
#include "./src/player/OnPlayerDisconnect.inc"