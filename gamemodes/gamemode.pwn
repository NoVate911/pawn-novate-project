/*

[ ============================== ]
   �������� ����� �������� ����
  READ BEFORE LAUNCHING THE MOD
[ ============================== ]

-- [ RUS ] --
������ ������ ���� �������� ������� �������������.
��������� ����������� ����� ����� ������������ � �������� ��� �� ����� �� ����� ��������.

���� ��������� ����������� �������, �� �������� ������ � ���������� "Windows 1251 (cp1251)".

-- [ ENG ] --
This build was written by a Russian developer.
Some translated text may be displayed with errors or will not be translated at all.

If unknown characters appear, then open the project with the encoding "Windows 1251 (cp1251)".

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
#include "./src/define.inc"
#include "./src/enum.inc"
#include "./src/config.inc"
#include "./src/utils.inc"

/*      [ ���������� ���� ]      */
/*      [ DIALOG BOXES ]      */
#include "./src/dialogs/Authorization.inc"
#include "./src/dialogs/Character.inc"
#include "./src/dialogs/Kick.inc"

/*      [ ��������� ������� ]      */
/*      [ SERVER SIDE ]      */
#include "./src/server/OnGameModeInit.inc"
#include "./src/server/OnGameModeExit.inc"

/*      [ ���������� ������� ]      */
/*      [ CLIENT SIDE ]      */
#include "./src/player/timers/OnPlayerSecond.inc"
#include "./src/player/OnPlayerConnect.inc"
#include "./src/player/OnPlayerDisconnect.inc"
#include "./src/player/OnPlayerText.inc"