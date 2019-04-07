        GS_WELCOME              dd     1
        GS_PAUSE                dd     2
        GS_RUN                  dd     3
        GS_GAMEOVER             dd     4

        TIMER_UPDATE            dd     18
        TIMER_BULLET            dd     200
        TIMER_EWAVE             dd     1000 ;after last enemy killed
        TIMER_METEOR            dd     3000
        TIMER_BONUS             dd     4000
        TIMER_SCORE             dd     1000
        TIMER_BACKGROUND        dd     50
        TIMER_ANIMATION         dd     20

        SND_ASYNC               equ    $0001
        SND_NODEFAULT           equ    $0002

        PBULLET_STATE_1         equ    1    ;player bullet state
        PBULLET_STATE_2         equ    2
        PBULLET_STATE_3         equ    3
        PBULLET_STATE_4         equ    4
        PBULLET_STATE_COUNT     equ    5    ;player bullet state count
        PBULLET_MAX             equ    200  ;player bullet max count

        PLAYER_STATE_MAX        equ    10

        EBULLET_MAX             equ    10   ;enemy bullet max count
        ENEMY_MAX               equ    9    ;enemy max count
        ENEMY_HP_MAX            equ    70    ;enemy max hp
        ENEMY_HP_MIN            equ    10    ;enemy min hp
        ENEMY_TYPE_COUNT        equ    4    ;high()
        BOSS_HP_MAX             equ    500  ;boss max hp
        BOSS_HP_MIN             equ    50   ;boss min hp
        PLAYER_HP               equ    100  ;player start hp
        PLAYER_HP_MAX           equ    100
        PLAYER_HP_BONUS         equ    10


        ENEMY_UNUSED            equ    0    ;enemy state
        ENEMY_ACTIVE            equ    1

        ENEMY_STATE_MAX         equ    4

        ENEMY_YMAX              dd     ?

        BONUS_STATE_COUNT       equ    8    ;bonus state count
        BONUS_TYPE_COUNT        equ    6
        BG_STATE_COUNT          equ    408   ;background states count
        BG_SPEED                equ    5

        sizeof.DWORD            equ    4
        sizeof.WORD             equ    2

        IMG_BG                  du     'images\bg.bmp', 0
        IMG_BONUS               du     'images\bonus.bmp', 0
        IMG_PLAYER              du     'images\player.bmp', 0
        IMG_ENEMY               du     'images\enemy.bmp', 0
        IMG_BOSS                du     'images\boss.bmp', 0
        IMG_PBULLET             du     'images\pbullet.bmp', 0
        IMG_EBULLET             du     'images\ebullet.bmp', 0
        IMG_START               du     'images\0start.bmp', 0
        IMG_CONTINUE            du     'images\0continue.bmp', 0
        IMG_RESTART             du     'images\0restart.bmp', 0
        IMG_EXIT                du     'images\0exit.bmp', 0
        IMG_SOUND               du     'images\0sound.bmp', 0
        IMG_GO                  du     'images\go.bmp', 0
        IMG_PLAYER_HP           du     'images\php.bmp', 0
        IMG_ENEMY_HP            du     'images\ehp.bmp', 0
        IMG_METEOR              du     'images\meteor.bmp', 0
        IMG_BOMB                du     'images\bomb.bmp', 0
        IMG_BOMB1               du     'images\bomb1.bmp', 0
        IMG_PROTON              du     'images\proton.bmp', 0
        IMG_WELCOME             du     'images\welcome.bmp', 0

        SND_BULLET              du     'sounds\bullet.wav', 0
        SND_START               du     'sounds\start.wav', 0
        SND_ENEMY_DIE           du     'sounds\enemy_die.wav', 0
        SND_ENEMY_FLY           du     'sounds\enemy_fly.wav', 0
        SND_GAMEOVER            du     'sounds\player_die.wav', 0

        FRECORD                 du      'record\record.int', 0
        BYTESWRITTEN            dd      ?
        SCORE                   du      'SCORE:          ', 0
        RECORD                  du      'RECORD:          ', 0
        HP                      du      'HEALTH POINTS: ', 0
        HP_NOW                  du      '000', 0
        HP_MAX                  du      '/ 100', 0
        E_WAVE                  du      'ENEMY WAVE: ', 0
        E_WAVE_N                du      '00', 0


        SCORE_TIME              equ    1
        SCORE_BONUS             equ    2
        SCORE_DAMAGE            equ    3
        SCORE_EDIE              equ    10
        METEOR_DAMAGE_MAX       equ    15
        METEOR_DAMAGE_MIN       equ    5
        BONUS_HP_MAX            equ    20

        WAVE_BOSS               equ     5


        ANIMATION_BOMB_MAX      equ    100
        ANIMATION_BOMB_STATE_MAX equ    8
        ANIMATION_PROTON_STATE_MAX equ  61
        AT_BOMB_ENEMY           equ     0   ;animation type
        AT_BOMB_PLAYER          equ     1

        BONUS_DIST              equ    5
        PLAYER_DIST             equ    9
        ENEMY_DIST              equ    2
        PBULLET_DIST            equ    10
        EBULLET_DIST            equ    7
        BOSS_DIST               equ    10
        BBULLET_DIST            equ    10
        METEOR_DIST             equ    8
