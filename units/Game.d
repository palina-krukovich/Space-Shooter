Background.state                dd              0
Background.hbm                  dd              BG_STATE_COUNT dup ?

GameOver.hbm                    dd              ?
GameOver.rect                   RECT

Welcome.hbm                     dd              ?
Welcome.rect                    RECT

;player
Player.hbm                      dd              ?
Player.x                        dd              ?
Player.y                        dd              ?
Player.width                    dd              ?
Player.height                   dd              ?
Player.hp                       dd              ?
Player.hp.hbm                   dd              ?
Player.state                    dd              ?

Player.Bullet.state             dd              PBULLET_STATE_1
Player.Bullet.hbm               dd              ? ;sprite
Player.Bullet.width             dd              PBULLET_MAX dup ?
Player.Bullet.height            dd              PBULLET_MAX dup ?
Player.Bullet.x                 dd              PBULLET_MAX dup ?
Player.Bullet.y                 dd              PBULLET_MAX dup ?
Player.Bullet.need              dd              0

Player.hpIndicator.x            dd              ?, ?, ?
Player.hpIndicator.y            dd              ?
Player.hp.ProgressBar.x         dd              ?
Player.hp.ProgressBar.y         dd              ?
Player.hp.ProgressBar.width     dd              ?
Player.hp.ProgressBar.height    dd              ?

;enemies
Enemy.count                     dd              ?
Enemy.hbm                       dd              ?
Enemy.width                     dd              ?
Enemy.height                    dd              ?
Enemy.type                      dd              ENEMY_MAX dup ?
Enemy.state                     dd              ENEMY_MAX dup ?
Enemy.starthp                   dd              ENEMY_MAX dup ?
Enemy.hp                        dd              ENEMY_MAX dup ?
Enemy.activity                  dd              ENEMY_MAX dup ENEMY_UNUSED
Enemy.x                         dd              ENEMY_MAX dup ?
Enemy.y                         dd              ENEMY_MAX dup ?
Enemy.ymax                      dd              ENEMY_MAX dup ?
Enemy.hp.hbm                    dd              ?

Enemy.Bullet.hbm                dd              ?
Enemy.Bullet.hp                 dd              ENEMY_MAX dup ?
Enemy.Bullet.x                  dd              ENEMY_MAX dup ?
Enemy.Bullet.y                  dd              ENEMY_MAX dup ?
Enemy.Bullet.width              dd              ?
Enemy.Bullet.height             dd              ?

Enemy.WaveIndicator.x           dd              ?, ?
Enemy.WaveIndicator.y           dd              ?

Boss.IsActive                   dd              ?
Boss.hbm                        dd              ?
Boss.width                      dd              ?
Boss.height                     dd              ?
Boss.hp                         dd              ?
Boss.x                          dd              ?
Boss.y                          dd              ?
Boss.ymax                       dd              ?

Boss.Bullet.hbm                 dd              ?
Boss.Bullet.x                   dd              EBULLET_MAX dup ?
Boss.Bullet.y                   dd              EBULLET_MAX dup ?
Boss.Bullet.speed               dd              ?

Meteor.hbm                      dd              ? ;sprite
Meteor.damage                   dd              0
Meteor.x                        dd              ?
Meteor.y                        dd              ?
Meteor.width                    dd              ?
Meteor.height                   dd              ?
Meteor.speed                    dd              ?

Bonus.hbm                       dd              ? ;sprite
Bonus.state                     dd              ?
Bonus.type                      dd              ?
Bonus.x                         dd              ?
Bonus.y                         dd              ?
Bonus.width                     dd              40
Bonus.height                    dd              40
Bonus.hp                        dd              ?

Animation.Bomb.state            dd              ANIMATION_BOMB_MAX dup 0
Animation.Bomb.hbm              dd              ?, ?
Animation.Bomb.x                dd              ANIMATION_BOMB_MAX dup ?
Animation.Bomb.y                dd              ANIMATION_BOMB_MAX dup ?
Animation.Bomb.width            dd              70
Animation.Bomb.height           dd              70
Animation.Bomb.IsActive         dd              ANIMATION_BOMB_MAX dup 0
Animation.Bomb.type             dd              ANIMATION_BOMB_MAX dup 0

Animation.Proton.hbm            dd              ?
Animation.Proton.x              dd              ?
Animation.Proton.y              dd              ?
Animation.Proton.width          dd              ?
Animation.Proton.height         dd              ?
Animation.Proton.state          dd              ?


;buttons
Game.state                      dd              GS_WELCOME
Game.Sound                      dd              1
Game.Score                      dd              0
Game.Record                     dd              0
Game.WaveCount                  dd              ?

Record.hf                       dd              ?

Timer.Update.TickCount          dd              ?
Timer.EWave.TickCount           dd              ?
Timer.Bullet.TickCount          dd              ?
Timer.Meteor.TickCount          dd              ?
Timer.Bonus.TickCount           dd              ?
Timer.Score.TickCount           dd              ?
Timer.Background.TickCount      dd              ?
Timer.Animation.TickCount       dd              ?

Start.hbm                       dd              ?, ?
Exit.hbm                        dd              ?, ?
Sound.hbm                       dd              ?, ?, ?
Continue.hbm                    dd              ?, ?
Restart.hbm                     dd              ?, ?

Welcome.Start.State             dd              0
Welcome.Start                   RECT

Welcome.Exit.State              dd              0
Welcome.Exit                    RECT

Welcome.Sound.State             dd              0

Pause.Continue.State            dd              ?
Pause.Continue                  RECT

Pause.Exit.State                dd              ?
Pause.Exit                      RECT

Pause.Sound.State               dd              ?

GameOver.Restart.State          dd              ?
GameOver.Restart                RECT

GameOver.Exit.State             dd              ?
GameOver.Exit                   RECT

Sound.State                     dd              ?
Sound                           RECT

Buffer.hdc                      dd              ?
Memory.hdc                      dd              ?
Buffer.hbm                      dd              ?
Red.hbr                         dd              ?
Red.hp                          dd              ?
Black.hbr                       dd              ?
Black.hp                        dd              ?
hfont                           dd              ?


