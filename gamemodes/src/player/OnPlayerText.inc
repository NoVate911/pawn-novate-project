public OnPlayerText(playerid, text[])
{
    if(IsPlayerNPC(playerid))
        return 1;

    if(!PInfo[playerid][IsLogged])
    {
        SCM(playerid, C_F_WHITE, ""NOTIF_ERROR" "C_WHITE"��� ������������� ���� ���������� ���� ����������������.");
        return Player_Kick(playerid, _, "�� �������������");
    }

    return 0;
}