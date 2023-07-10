dCreate:Dlg_Auth_Log_Password(playerid)
{
    static const message[] = "\
    "C_WHITE"\n\\c� ������������ �� ������ "C_EMERALD""SERVER_NAME" "C_WHITE"| "C_EMERALD""SERVER_TYPE""C_WHITE".\n\
    "C_WHITE"\\c��� ����� ����������� ���� ������.\n\
    "C_WHITE"\\c������� ���� ������ � ���� ����� � ������� \"������\"\n\n";
    return Dialog_Open(playerid, Dialog:Dlg_Auth_Log_Password, DIALOG_STYLE_PASSWORD, ""C_GRAY"�������������� "C_BLACK"| "C_WHITE"�����������", message, "������", "�����");
}

dResponse:Dlg_Auth_Log_Password(playerid)
{
    if(response)
    {
        if(!strlen(inputtext))
        {
            SCM(playerid, C_F_WHITE, ""NOTIF_ERROR" "C_WHITE"��� ���� ������ ���� ���������.");
            return Dialog_Show(playerid, Dialog:Dlg_Auth_Log_Password);
        }

        if(!(MIN_PASSWORD_LEN < strlen(inputtext) < MAX_PASSWORD_LEN))
        {
            SCM(playerid, C_F_WHITE, ""NOTIF_ERROR" "C_WHITE"������ ������� ������� ��� ��������.");
            return Dialog_Show(playerid, Dialog:Dlg_Auth_Log_Password);
        }

        new Regex:regex_password_check = Regex_New("^[a-zA-Z0-9]{1,}$");
        if(Regex_Check(inputtext, regex_password_check))
        {
            strmid(PInfo[playerid][Password], inputtext, 0, strlen(inputtext), MAX_PASSWORD_LEN);

            static const query[] = "SELECT email,regIP,lastIP,regDate,lastDate FROM accounts WHERE password = md5('%s') LIMIT 1";
            new mysql[sizeof(query)+(-2+MAX_PASSWORD_LEN)];
            mysql_format(SInfo[MySQL], mysql, sizeof(mysql), query, PInfo[playerid][Password]);
            new Cache:cache = mysql_query(SInfo[MySQL], mysql, true);
            if(cache_num_rows())
            {
                Data_Get_PlayerInfo(playerid);
                Player_CharacterShow(playerid);
                SCM(playerid, C_F_WHITE, ""NOTIF_SUCCESS" "C_WHITE"�� �������������� �� �������.");
                printf("%s ����� %s(%d) [%s] ������������� �� �������.", DEBUG_INFO, PInfo[playerid][Nick], playerid, PInfo[playerid][LastIP]);

                static const query_update[] = "UPDATE accounts SET lastIP = '%s', lastDate = '%s' WHERE nick = '%s' LIMIT 1";
                new mysql_update[sizeof(query_update)+(-2+15)+(-2+12)+(-2+MAX_PLAYER_NAME)];
                mysql_format(SInfo[MySQL], mysql_update, sizeof(mysql_update), query_update, PInfo[playerid][LastIP], PInfo[playerid][LastDate], PInfo[playerid][Nick]);
                mysql_query(SInfo[MySQL], mysql_update, false);
            }
            else
            {
                PInfo[playerid][AuthorizationCountTry]--;
                
                if(PInfo[playerid][AuthorizationCountTry] < 0)
                {
                    Player_Kick(playerid, _, "����� ������� �����");
                }
                else
                {
                    SCMf(playerid, C_F_WHITE, ""NOTIF_ERROR" "C_WHITE"������ ����� �������. �������� "C_EMERALD"%d "C_WHITE"�������.", PInfo[playerid][AuthorizationCountTry]);
                    Dialog_Show(playerid, Dialog:Dlg_Auth_Log_Password);
                }
            }
            cache_delete(cache);
        }
        else
        {
            SCM(playerid, C_F_WHITE, ""NOTIF_ERROR" "C_WHITE"������ ����� �������� �� ����/����� � ��������� ��������.");
            Dialog_Show(playerid, Dialog:Dlg_Auth_Log_Password);
        }
        Regex_Delete(regex_password_check);
    }
    else
    {
        Player_Kick(playerid, "������", "�����");
    }
    return 1;
}

dCreate:Dlg_Auth_Reg_Password(playerid)
{
    static const message[] = "\
    "C_WHITE"\n\\c����� ���������� �� ������ "C_EMERALD""SERVER_NAME" "C_WHITE"| "C_EMERALD""SERVER_TYPE""C_WHITE".\n\
    "C_WHITE"\\c�� ������ ����� �� ���������������� �� ������ ��������.\n\
    "C_WHITE"\\c��� �����������, ������� ������ � ���� ����� � ������� "C_EMERALD"\"�����\""C_WHITE".\n\n";
    return Dialog_Open(playerid, Dialog:Dlg_Auth_Reg_Password, DIALOG_STYLE_INPUT, ""C_GRAY"�������������� "C_BLACK"| "C_WHITE"�����������", message, "�����", "�����");
}

dResponse:Dlg_Auth_Reg_Password(playerid)
{
    if(response)
    {
        if(!strlen(inputtext))
        {
            SCM(playerid, C_F_WHITE, ""NOTIF_ERROR" "C_WHITE"��� ���� ������ ���� ���������.");
            return Dialog_Show(playerid, Dialog:Dlg_Auth_Reg_Password);
        }

        if(!(MIN_PASSWORD_LEN < strlen(inputtext) < MAX_PASSWORD_LEN))
        {
            SCM(playerid, C_F_WHITE, ""NOTIF_ERROR" "C_WHITE"������ ������� ������� ��� ��������.");
            return Dialog_Show(playerid, Dialog:Dlg_Auth_Reg_Password);
        }

        new Regex:regex_password_check = Regex_New("^[a-zA-Z0-9]{1,}$");
        if(Regex_Check(inputtext, regex_password_check))
        {
            strmid(PInfo[playerid][Password], inputtext, 0, strlen(inputtext), MAX_PASSWORD_LEN);
            Dialog_Show(playerid, Dialog:Dlg_Auth_Reg_Email);
        }
        else
        {
            SCM(playerid, C_F_WHITE, ""NOTIF_ERROR" "C_WHITE"������ ����� �������� �� ����/����� � ��������� ��������.");
            Dialog_Show(playerid, Dialog:Dlg_Auth_Reg_Password);
        }
        Regex_Delete(regex_password_check);
    }
    else
    {
        Player_Kick(playerid, "������", "�����");
    }
    return 1;
}

dCreate:Dlg_Auth_Reg_Email(playerid)
{
    static const message[] = "\
    "C_WHITE"\n\\c������ ������ �� ������������.\n\
    "C_WHITE"\\c������� ���� ����������� ����� � ���� ����� � ������� "C_EMERALD"\"�����\""C_WHITE".\n\n";
    return Dialog_Open(playerid, Dialog:Dlg_Auth_Reg_Email, DIALOG_STYLE_INPUT, ""C_GRAY"�������������� "C_BLACK"| "C_WHITE"�����������", message, "�����", "");
}

dResponse:Dlg_Auth_Reg_Email(playerid)
{
    if(response)
    {
        if(!strlen(inputtext))
        {
            SCM(playerid, C_F_WHITE, ""NOTIF_ERROR" "C_WHITE"��� ���� ������ ���� ���������.");
            return Dialog_Show(playerid, Dialog:Dlg_Auth_Reg_Email);
        }

        if(!(MIN_EMAIL_LEN < strlen(inputtext) < MAX_EMAIL_LEN))
        {
            SCM(playerid, C_F_WHITE, ""NOTIF_ERROR" "C_WHITE"����� ����������� ����� ������� ������� ��� ��������.");
            return Dialog_Show(playerid, Dialog:Dlg_Auth_Reg_Email);
        }

        new Regex:regex_email_check = Regex_New("^[a-zA-Z0-9.-_]{1,43}@[a-zA-Z]{1,12}.[a-zA-Z]{1,8}$");
        if(Regex_Check(inputtext, regex_email_check))
        {
            strmid(PInfo[playerid][Email], inputtext, 0, strlen(inputtext), MAX_EMAIL_LEN);
            new year, month, day, hour, minute, second, date[15], time[15];
            getdate(year, month, day);
            gettime(hour, minute, second);
            format(date, sizeof(date), "%02d.%02d.%02d", year, month, day);
            format(time, sizeof(time), "%02d:%02d:%02d", hour, minute, second);
            format(PInfo[playerid][RegDate], 22, "%s / %s", date, time);
            format(PInfo[playerid][LastDate], 22, "%s / %s", date, time);
            GetPlayerIp(playerid, PInfo[playerid][RegIP], 16);
            GetPlayerIp(playerid, PInfo[playerid][LastIP], 16);

            static const query[] = "INSERT INTO accounts (nick,password,email,regIP,lastIP,regDate,lastDate) VALUES ('%s',md5('%s'),'%s','%s','%s','%s','%s')";
            new mysql[sizeof(query)+(-2+MAX_PLAYER_NAME)+(-2+MAX_PASSWORD_LEN)+(-2+MAX_EMAIL_LEN)+(-2+16)+(-2+16)+(-2+22)+(-2+22)];
            mysql_format(SInfo[MySQL], mysql, sizeof(mysql), query, PInfo[playerid][Nick], PInfo[playerid][Password], PInfo[playerid][Email], PInfo[playerid][RegIP], PInfo[playerid][LastIP], PInfo[playerid][RegDate], PInfo[playerid][LastDate]);
            new Cache:cache = mysql_query(SInfo[MySQL], mysql, true);
            if(cache_num_results())
            {
                Player_CharacterShow(playerid);
                SCM(playerid, C_F_WHITE, ""NOTIF_SUCCESS" "C_WHITE"�� ������������������ �� �������.");
                printf("%s ����� %s(%d) [%s] ����������������� �� �������.", DEBUG_INFO, PInfo[playerid][Nick], playerid, PInfo[playerid][RegIP]);
            }
            cache_delete(cache);
        }
        else
        {
            SCM(playerid, C_F_WHITE, ""NOTIF_ERROR" "C_WHITE"�������� ����� ����������� �����.");
            Dialog_Show(playerid, Dialog:Dlg_Auth_Reg_Email);
        }
        Regex_Delete(regex_email_check);
    }
    return 1;
}