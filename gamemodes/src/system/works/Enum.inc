enum WorkInfo
{
    ActorID,
    STREAMER_TAG_CP:Checkpoint,
    STREAMER_TAG_3D_TEXT_LABEL:Actor3DText,
}
new WInfo[MAX_INITIAL_WORKS][WorkInfo];

enum PlayerWorkInfo
{
    // Общее | General
    STREAMER_TAG_CP:Checkpoint, // Чекпоинт | Checkpoint

    // Грузчик | Loader
    LoaderMovedBoxCount, // Ящики | Boxes
    bool:LoaderIsPickup, // Поднято ли? | Is it raised?

    // Фермер | Farmer
    FarmerMovedHayCount, // Снопы сена | Sheaves of hay
    bool:FarmerIsPickup, // Поднято ли? | Is it raised?

    // Дайвер | Diver
    DiverTakenMarkCount, // Взято меток | Tags taken
    DiverTotalTakenMarkCount, // Общее количество взятых меток | Total number of tags taken
    Float:DiverCheckpointPosition[3], // Позиция чекпоинтов | Checkpoint position
    bool:DiverIsAir, // Есть ли воздух? | Is there air?
}
new PWInfo[MAX_PLAYERS][PlayerWorkInfo];