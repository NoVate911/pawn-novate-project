/*      [ АВТОРИЗАЦИЯ/РЕГИСТРАЦИЯ ]      */
/*      [ AUTHORIZATION/REGISTRATION ]      */
#define MAX_AUTHORIZATION_TIME      (120) // Максимальное время авторизации (в секундах) | Maximum authorization time (in seconds)
#define MAX_REGISTRATION_TIME       (180) // Максимальное время регистрации (в секундах) | Maximum registration time (in seconds)
#define AUTHORIZATION_COUNT_TRY     (3) // Максимальное количество попыток входа | Maximum number of login attempts

#define MAX_PASSWORD_LEN            (32) // Максимальная длина пароля | Maximum password length
#define MIN_PASSWORD_LEN            (4) // Минимальная длина пароля | Minimum password length

#define MAX_EMAIL_LEN               (64) // Максимальная длина почты | Maximum mail length
#define MIN_EMAIL_LEN               (1) // Минимальная длина почты | Minimum mail length

#define MAX_POSITIONS_SPAWN         (1) // Максимальное количество позиций для спавна | Maximum number of spawn positions

/*      [ ПЕРСОНАЖ ]      */
/*      [ CHARACTER ]      */
#define MAX_CHARACTERS              (1) // Максимальное количество персонажей | Maximum number of characters

#define MAX_CHARACTER_AGE           (60) // Максимальный возраст персонажа | Maximum age of the character
#define MIN_CHARACTER_AGE           (18) // Минимальный возраст персонажа | Minimum age of the character

/*      [ АДМИНИСТРИРОВАНИЕ ]      */
/*      [ ADMINISTRATION ]      */
#define MAX_ADMIN_LEVEL             (6) // Максимальный уровень Администратора | Maximum Administrator Level
#define MIN_ADMIN_LEVEL             (1) // Минимальный уровень Администратора | Minimum Administrator Level

/*      [ ЧАТ ]      */
/*      [ CHAT ]      */
#define MAX_DISTANCE_CHAT           (10.0) // Максимальная дистанция отправки сообщений | Maximum distance for sending messages
#define MAX_DELAY_SEND_MESSAGE_CHAT (2) // Максимальное время задержки после отправки сообщения (в секундах) | Maximum delay time after sending a message (in seconds)
#define MAX_DELAY_SEND_COMMAND_CHAT (3) // Максимальное время задержки после отправки команды (в секундах) | Maximum delay time after sending a command (in seconds)

/*      [ УРОВЕНЬ/ОПЫТ ]      */
/*      [ LEVEL/EXP ]      */
#define MAX_LEVEL                   (100) // Максимальное количество уровней | Maximum number of levels

#define MAX_EXP_UPDATE_LEVEL        (2) // Максимальное количество опыта для повышения уровня | Maximum amount of experience to level up
#define MAX_TIME_UPDATE_LEVEL       (3600) // Время обновления уровня/опыта игрока (в секундах) | Player Level/Experience Update Time (in seconds)

/*      [ AFK ]      */
/*      [ AFK ]      */
#define MAX_AFK_TIME_SET            (60) // Время после которого игрок будет входить в AFK (в секундах) | The time after which the player will enter AFK (in seconds)
#define MAX_AFK_TIME_WARNING        (60) // Время после которого будет выводиться предупреждение (в секундах) | The time after which the warning will be displayed (in seconds)

/*      [ ДЕНЬГИ ]      */
/*      [ MONEY ]      */
#define MAX_TIME_UPDATE_MONEY       (60) // Время обновления денег у игрока (в секундах) | The player's money update time (in seconds)

/*      [ ЗАРПЛАТА ]      */
/*      [ PAYDAY ]      */
#define MAX_PAYDAY_BENEFIT          (500) // Пособие по безработице | Unemployment benefits

/*      [ ДИАЛОГИ ]      */
/*      [ DIALOGUES ]      */
#define MAX_DELAY_OPENING_DIALOG    (2) // Максимальное время задержки открытия диалога (в секундах) | The maximum delay time for opening a dialog (in seconds)

/*      [ АВТОШКОЛА ]      */
/*      [ DRIVING SCHOOL ]      */
#define MAX_DRIVING_SCHOOL          (1) // Максимальное количество автошкол | The maximum number of driving schools
#define MAX_DRIVING_SCHOOL_LICENSES (2) // Максимальное количество лицензий | Maximum number of licenses