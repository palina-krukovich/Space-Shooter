proc Game.Run
       mov        [Game.state], GS_RUN
       stdcall    Calc.Coordinates
       stdcall    Game.InitEnemy
       stdcall    Game.InitBullet
       stdcall    Game.InitPlayer
       stdcall    Game.InitScore
       invoke     GetTickCount
       mov        [Timer.EWave.TickCount], eax
       mov        [Timer.Bullet.TickCount], eax
       mov        [Timer.Meteor.TickCount], eax
       mov        [Timer.Bonus.TickCount], eax
       mov        [Timer.Score.TickCount], eax
       mov        [Timer.Animation.TickCount], eax
       ;mov        [Timer.Update.TickCount], eax
       ret
endp

proc Game.InitPlayer
      mov         [Player.hp], PLAYER_HP
      mov         [Player.state], 0
      ret
endp

proc Game.InitScore uses ecx
      mov         [Game.Score], 0
      mov         ecx, 7
   .loop:
      mov         [SCORE + ecx * 2], ' '
      add         ecx, 1
      cmp         ecx, 15
      jne         .loop
      ret
endp

proc Game.InitEnemy uses ecx edi esi
      mov         [Enemy.count], 1
      mov         [Game.WaveCount], 0
      mov         edi, [MainWindow.ClientRect.right]
      mov         esi, [MainWindow.ClientRect.bottom]
      xor         ecx, ecx
.init_enemy:
      mov         [Enemy.x + ecx * sizeof.DWORD], edi
      mov         [Enemy.Bullet.x + ecx * sizeof.DWORD], edi
      mov         [Enemy.y + ecx * sizeof.DWORD], esi                           ; --
      mov         [Enemy.Bullet.y + ecx * sizeof.DWORD], esi                    ; --
      mov         [Enemy.activity + ecx * sizeof.DWORD], ENEMY_UNUSED        ;   *
      mov         [Enemy.ymax + ecx * sizeof.DWORD], ENEMY_DIST
      mov         [Enemy.hp + ecx * sizeof.DWORD], 0
      mov         [Enemy.state + ecx * sizeof.DWORD], 0
      add         ecx, 1
      cmp         ecx, ENEMY_MAX
      jb          .init_enemy
      ret
endp

proc Game.InitBullet uses edi esi ecx
      mov         [Player.Bullet.state], PBULLET_STATE_1
      mov         [Player.Bullet.need], 0
      mov         edi, [MainWindow.ClientRect.right]
      mov         esi, [MainWindow.ClientRect.bottom]
      ;meteor
      mov         [Meteor.x], edi
      mov         [Meteor.y], esi
      ;bonus
      mov         [Bonus.x], edi
      mov         [Bonus.y], esi
      mov         [Bonus.hp], 1
      xor         ecx, ecx
.init_bullet:
      mov         [Player.Bullet.x + ecx * sizeof.DWORD], edi    ; --*
      mov         [Player.Bullet.y + ecx * sizeof.DWORD], 0      ; --
      add         ecx, 1
      cmp         ecx, PBULLET_MAX
      jb          .init_bullet

      xor         ecx, ecx
.init_bomb:
      mov         [Animation.Bomb.IsActive + ecx * sizeof.DWORD], 0
      mov         [Animation.Bomb.x + ecx * sizeof.DWORD], edi
      mov         [Animation.Bomb.y + ecx * sizeof.DWORD], esi
      mov         [Animation.Bomb.state + ecx * sizeof.DWORD], 0
      mov         [Animation.Bomb.type + ecx * sizeof.DWORD], 0
      add         ecx, 1
      cmp         ecx, ANIMATION_BOMB_MAX
      jb          .init_bomb
      ret
endp

proc Game.Run.Update uses eax esi,\
     TickCount
      mov         esi, [TickCount]
      mov         eax, [Timer.Bonus.TickCount]
      add         eax, [TIMER_BONUS]
      cmp         eax, esi
      jb          .bonus
      mov         eax, [Timer.Meteor.TickCount]
      add         eax, [TIMER_METEOR]
      cmp         eax, esi
      jb          .meteor
      mov         eax, [Timer.Score.TickCount]
      add         eax, [TIMER_SCORE]
      cmp         eax, esi
      jb          .score
      mov         eax, [Timer.EWave.TickCount]
      add         eax, [TIMER_EWAVE]
      cmp         eax, esi
      jb          .ewave
      mov         eax, [Timer.Animation.TickCount]
      add         eax, [TIMER_ANIMATION]
      cmp         eax, esi
      jb          .animation
      mov         eax, [Timer.Bullet.TickCount]
      add         eax, [TIMER_BULLET]
      cmp         eax, esi
      jb          .bullet
      ;mov         eax, [Timer.Update.TickCount]
      ;add         eax, [TIMER_UPDATE]
      ;cmp         eax, esi
      ;jb          .update
      ;jmp         .EndProc
.update:
      stdcall     Game.Run.Update.ProcessInput
      stdcall     Game.Run.Update.Bullet
      stdcall     Game.Run.Update.Enemy
      stdcall     Game.Run.Update.EnemyCrash
      stdcall     Game.Run.Update.PlayerCrash
      stdcall     Game.Run.Update.Meteor
      stdcall     Game.Run.Update.Bonus
      stdcall     Game.Run.Update.Record
      invoke      InvalidateRect, [MainWindow.hWnd], 0, 0
      ;mov         [Timer.Update.TickCount], esi
      jmp         .EndProc
.bonus:
      stdcall     Game.Run.Bonus
      mov         [Timer.Bonus.TickCount], esi
      jmp         .EndProc
.meteor:
      stdcall     Game.Run.Meteor
      mov         [Timer.Meteor.TickCount], esi
      jmp         .EndProc
.score:
      add         [Game.Score], SCORE_TIME
      mov         [Timer.Score.TickCount], esi
      jmp         .EndProc
.ewave:
      stdcall     Game.Run.CheckEnemy
      mov         [Timer.EWave.TickCount], esi
      jmp         .EndProc
.bullet:
      stdcall     Game.Run.Bullet
      mov         [Timer.Bullet.TickCount], esi
      jmp         .EndProc
.animation:
      stdcall     Game.Run.Update.Animation
      stdcall     Game.Run.Update.PlayerState
      stdcall     Game.Run.Update.EnemyState
      mov         [Timer.Animation.TickCount], esi
      jmp         .EndProc
.EndProc:
      ret
endp

proc Game.Run.Update.ProcessInput uses edi eax edx
      mov         edi, PLAYER_DIST
      invoke      GetKeyState, VK_LEFT
      and         eax, $8000
      shr         eax, 15
      mul         edi
      sub         [Player.x], eax
      stdcall     Game.CheckCoordinates, [Player.x], [Player.y], 0, 0, [MainWindow.ClientRect.right], [MainWindow.ClientRect.bottom]
      xor         eax, 1
      mul         edi
      add         [Player.x], eax

      invoke      GetKeyState, VK_RIGHT
      and         eax, $8000
      shr         eax, 15
      mul         edi
      add         [Player.x], eax
      mov         eax, [Player.x]
      add         eax, [Player.width]
      stdcall     Game.CheckCoordinates, eax, [Player.y], 0, 0, [MainWindow.ClientRect.right], [MainWindow.ClientRect.bottom]
      xor         eax, 1
      mul         edi
      sub         [Player.x], eax

      invoke      GetKeyState, VK_DOWN
      and         eax, $8000
      shr         eax, 15
      mul         edi
      add         [Player.y], eax
      mov         eax, [Player.y]
      add         eax, [Player.height]
      stdcall     Game.CheckCoordinates, [Player.x], eax, 0, 0, [MainWindow.ClientRect.right], [MainWindow.ClientRect.bottom]
      xor         eax, 1
      mul         edi
      sub         [Player.y], eax

      invoke      GetKeyState, VK_UP
      and         eax, $8000
      shr         eax, 15
      mul         edi
      sub         [Player.y], eax
      stdcall     Game.CheckCoordinates, [Player.x], [Player.y], 0, 0, [MainWindow.ClientRect.right], [MainWindow.ClientRect.bottom]
      xor         eax, 1
      mul         edi
      add         [Player.y], eax

      invoke      GetKeyState, VK_SPACE
      and         eax, $8000
      jz          .no_bullet
      mov         [Player.Bullet.need], 1
.no_bullet:

      invoke      GetKeyState, VK_ESCAPE
      and         eax, $8000
      jz          .no_pause
      stdcall     Game.Pause
.no_pause:

      ret
endp

proc Game.Run.Update.PlayerState uses eax edx ebx
      mov         eax, [Player.state]
      add         eax, 1
      mov         ebx, PLAYER_STATE_MAX
      xor         edx, edx
      div         ebx
      mov         [Player.state], edx
      ret
endp

proc Game.Run.Update.EnemyState uses ecx eax edx esi
      xor         ecx, ecx
.update_enemy:
      mov         eax, [Enemy.state + ecx * sizeof.DWORD]
      add         eax, 1
      mov         esi, ENEMY_STATE_MAX
      xor         edx, edx
      div         esi
      mov         [Enemy.state + ecx * sizeof.DWORD], edx
      add         ecx, 1
      cmp         ecx, [Enemy.count]
      jb          .update_enemy
      ret
endp

proc Game.Run.Update.Record
       mov      eax, [Game.Score]
       cmp      eax, [Game.Record]
       jb       .EndProc
       mov      [Game.Record], eax
.EndProc:
       ret
endp

proc Game.Run.Update.Enemy uses ecx eax esi
      xor         ecx, ecx
.update_enemy:
      stdcall     Calc.AddMod, [Enemy.y + ecx * sizeof.DWORD], ENEMY_DIST, [Enemy.ymax + ecx * sizeof.DWORD]
      mov         [Enemy.y + ecx * sizeof.DWORD], eax
      add         ecx, 1
      cmp         ecx, [Enemy.count]
      jb          .update_enemy
      stdcall     Game.Run.Update.EBullet
      ret
endp

proc Game.Run.Update.EnemyCrash uses esi edi
      xor         esi, esi
.enemy:
      xor         edi, edi
.bullet:
      cmp         [Enemy.activity + esi * sizeof.DWORD], ENEMY_ACTIVE
      jne         .continue
      mov         eax, [Enemy.height]
      sub         eax, 50
      stdcall     Game.CheckCoordinates, [Player.Bullet.x + edi * sizeof.DWORD], [Player.Bullet.y + edi * sizeof.DWORD], [Enemy.x + esi * sizeof.DWORD], [Enemy.y + esi * sizeof.DWORD], [Enemy.width], eax
      test        eax, eax
      jz          .continue
      ;hide bullet
      mov         eax, [Player.Bullet.y + edi * sizeof.DWORD]
      sub         eax, 35
      stdcall     Game.Run.Animation.Bomb, [Player.Bullet.x + edi * sizeof.DWORD], eax, 50, 50, 0
      mov         ebx, [MainWindow.ClientRect.right]
      mov         [Player.Bullet.x + edi * sizeof.DWORD], ebx
      mov         [Player.Bullet.y + edi * sizeof.DWORD], 0
      ;sub enemy hp
      add         [Game.Score], SCORE_DAMAGE
      sub         [Enemy.hp + esi * sizeof.DWORD], 1
      jnz         .continue
      ;enemy die
      add         [Game.Score], SCORE_EDIE
      mov         [Enemy.activity + esi * sizeof.DWORD], ENEMY_UNUSED
      mov         [Enemy.Bullet.x + + esi * sizeof.DWORD], ebx
      mov         [Enemy.x + esi * sizeof.DWORD], ebx
.continue:
      add         edi, 1
      cmp         edi, PBULLET_MAX
      jb          .bullet
      add         esi, 1
      cmp         esi, [Enemy.count]
      jb          .enemy
      ret
endp

proc Game.Run.Animation.Bomb uses esi edi eax,\
      x, y, width, height, type
      mov         edi, [x]
      cmp         edi, [MainWindow.ClientRect.right]
      jns          .EndProc
      xor         esi, esi
.find_unused_animation:
      mov         eax, [Animation.Bomb.IsActive + esi * sizeof.DWORD]
      test        eax, eax
      jnz         .continue
      mov         [Animation.Bomb.IsActive + esi * sizeof.DWORD], 1
      mov         edi, [x]
      mov         [Animation.Bomb.x + esi * sizeof.DWORD], edi
      mov         edi, [y]
      mov         [Animation.Bomb.y + esi * sizeof.DWORD], edi
      mov         edi, [width]
      mov         [Animation.Bomb.width + esi * sizeof.DWORD], edi
      mov         edi, [height]
      mov         [Animation.Bomb.height + esi * sizeof.DWORD], edi
      mov         edi, [type]
      mov         [Animation.Bomb.type + esi * sizeof.DWORD], edi
      mov         [Animation.Bomb.state + esi * sizeof.DWORD], 0
      jmp         .EndProc
.continue:
      add         esi, 1
      cmp         esi, ANIMATION_BOMB_MAX
      jb          .find_unused_animation
.EndProc:
      ret
endp

proc Game.Run.Update.Animation uses esi eax
      xor         esi, esi
.update_animation:
      mov         eax, [Animation.Bomb.IsActive + esi * sizeof.DWORD]
      test        eax, eax
      jz          .continue
      add         [Animation.Bomb.state + esi * sizeof.DWORD], 1
      cmp         [Animation.Bomb.state + esi * sizeof.DWORD], ANIMATION_BOMB_STATE_MAX
      jb          .continue
      mov         [Animation.Bomb.IsActive + esi * sizeof.DWORD], 0
.continue:
      add         esi, 1
      cmp         esi, ANIMATION_BOMB_MAX
      jb          .update_animation
      ret
endp

proc Game.Run.Update.PlayerCrash uses esi edi ecx eax
;player <-> enemy bullet
      xor         esi, esi
.enemy_bullet:
      stdcall     Game.CheckCoordinates, [Enemy.Bullet.x + esi * sizeof.DWORD], [Enemy.Bullet.y + esi * sizeof.DWORD], [Player.x], [Player.y], [Player.width], [Player.height]
      test        eax, eax
      jz          .continue
      mov         eax, [Enemy.Bullet.y + esi * sizeof.DWORD]
      add         eax, 15
      stdcall     Game.Run.Animation.Bomb, [Enemy.Bullet.x + esi * sizeof.DWORD], eax, 45, 45, 1
      ;hide bullet
      mov         ebx, [MainWindow.ClientRect.right]
      mov         [Enemy.Bullet.x + esi * sizeof.DWORD], ebx
      ;sub player hp
      mov         eax, [Enemy.Bullet.hp + esi * sizeof.DWORD]
      sub         [Player.hp], eax
      mov         eax, [Player.hp]
      test        eax, eax
      js          .gameover

.continue:
      add         esi, 1
      cmp         esi, [Enemy.count]
      jb          .enemy_bullet

;meteor <-> player
      mov         esi, [Meteor.width]
      shr         esi, 1
      add         esi, [Meteor.x]
      mov         edi, [Meteor.y]
      add         edi, [Meteor.height]
      stdcall     Game.CheckCoordinates, esi, edi, [Player.x], [Player.y], [Player.width], [Player.height]
      test        eax, eax
      jz          .no_meteor_crash
      add         edi, 15
      stdcall     Game.Run.Animation.Bomb, esi, edi, 60, 60, 1
      mov         ebx, [MainWindow.ClientRect.right]
      mov         [Meteor.x], ebx
      mov         eax, [Meteor.damage]
      sub         [Player.hp], eax
      mov         eax, [Player.hp]
      test        eax, eax
      js          .gameover
.no_meteor_crash:

;bonus <-> player
      mov         esi, [Bonus.width]
      shr         esi, 1
      add         esi, [Bonus.x]
      mov         edi, [Bonus.y]
      add         edi, [Bonus.height]
      stdcall     Game.CheckCoordinates, esi, edi, [Player.x], [Player.y], [Player.width], [Player.height]
      test        eax, eax
      jz          .no_bonus

      add         [Game.Score], SCORE_BONUS
      mov         edi, [MainWindow.ClientRect.right]
      mov         [Bonus.x], edi

      mov         eax, [Player.hp]
      add         eax, [Bonus.hp]
      mov         esi, PLAYER_HP_MAX
      add         esi, 1
      xor         edx, edx
      div         esi
      test        eax, eax
      jz          .no_overflow
      mov         [Player.hp], PLAYER_HP_MAX
      jmp         .no_bonus
     .no_overflow:
      mov         [Player.hp], edx
.no_bonus:

;enemy <-> player
      xor         ecx, ecx
.loop_player_enemy:
      mov         esi, [Enemy.y + ecx * sizeof.DWORD]
      add         esi, [Enemy.height + ecx * sizeof.DWORD]
      mov         edi, [Player.y]
      add         edi, 10
      cmp         esi, edi
      jb          .next_iteration
      mov         edi, [Player.y]
      add         edi, [Player.height]
      sub         edi, 10
      mov         esi, [Enemy.y + ecx * sizeof.DWORD]
      cmp         esi, edi
      ja          .next_iteration
      mov         esi, [Enemy.x + ecx * sizeof.DWORD]
      add         esi, [Enemy.width + ecx * sizeof.DWORD]
      mov         edi, [Player.x]
      add         edi, 10
      cmp         esi, edi
      jb          .next_iteration
      mov         edi, [Player.x]
      add         edi, [Player.width]
      sub         edi, 10
      mov         esi, [Enemy.x + ecx * sizeof.DWORD]
      cmp         esi, edi
      ja          .next_iteration
      stdcall     Game.GameOver
      jmp         .EndProc
   .next_iteration:
      add         ecx, 1
      cmp         ecx, [Enemy.count]
      jb          .loop_player_enemy
      jmp         .EndProc
.gameover:
      stdcall     Game.GameOver
.EndProc:
      ret
endp

proc Game.Run.CheckEnemy uses ecx esi
      xor         esi, esi
      xor         ecx, ecx
.check_enemy:
      cmp         [Enemy.activity + ecx * sizeof.DWORD], ENEMY_ACTIVE
      je          .EndProc
      add         ecx, 1
      cmp         ecx, [Enemy.count]
      jb          .check_enemy
      stdcall     Game.Run.EWave
.EndProc:
      ret
endp

proc Game.Run.EWave uses eax ebx ecx edx edi esi
      mov         edi, [MainWindow.ClientRect.right]
      sub         edi, [Enemy.width]
      xor         ecx, ecx
.ewave:
      ;x
  .choose_x:
      stdcall     Random, 0, edi
      mov         edx, eax
      xor         ebx, ebx
   .cmp_equal:
      mov         eax, edx
      add         eax, [Enemy.width]
      cmp         eax, [Enemy.x + ebx * sizeof.DWORD]
      jb          .cmp_continue
      mov         eax, [Enemy.x + ebx * sizeof.DWORD]
      add         eax, [Enemy.width]
      cmp         eax, edx
      jb          .cmp_continue
      jmp         .choose_x
     .cmp_continue:
      add         ebx, 1
      cmp         ebx, ecx
      jb          .cmp_equal
      mov         [Enemy.x + ecx * sizeof.DWORD], edx
      ;y
      mov         [Enemy.y + ecx * sizeof.DWORD], 0
      ;ymax
      stdcall     Random, ENEMY_DIST, [ENEMY_YMAX]
      mov         [Enemy.ymax + ecx * sizeof.DWORD], eax
      ;hp
      stdcall     Random, ENEMY_HP_MIN, ENEMY_HP_MAX
      mov         [Enemy.hp + ecx * sizeof.DWORD], eax
      mov         [Enemy.starthp + ecx * sizeof.DWORD], eax
      ;type
      stdcall     Random, 0, ENEMY_TYPE_COUNT
      mov         [Enemy.type + ecx * sizeof.DWORD], eax
      mov         [Enemy.Bullet.hp + ecx * sizeof.DWORD], eax
      add         [Enemy.Bullet.hp + ecx * sizeof.DWORD], 1
      mov         [Enemy.state + ecx * sizeof.DWORD], 0
      ;make active
      mov         [Enemy.activity + ecx * sizeof.DWORD], ENEMY_ACTIVE
      ;bullet
      stdcall     Game.Run.EnemyBullet, ecx
      add         ecx, 1
      cmp         ecx, [Enemy.count]
      jb          .ewave

      stdcall     Calc.AddMod, [Enemy.count], 1, ENEMY_MAX
      mov         [Enemy.count], eax
      ;increase bulet count every 4 wave
      add         [Game.WaveCount], 1
      mov         eax, [Game.WaveCount]
      xor         edx, edx
      mov         esi, 4
      div         esi
      test        edx, edx
      jnz         .no_bullet_increase
      stdcall     Calc.AddMod, [Player.Bullet.state], 1, PBULLET_STATE_COUNT
      mov         [Player.Bullet.state], eax
.no_bullet_increase:
      ret
endp

proc Game.Run.EnemyBullet uses eax ecx,\
      num
      mov         ecx, [num]
      stdcall     Calc.GetCenterCoord, [Enemy.width], [Enemy.Bullet.width]
      add         eax, [Enemy.x + ecx * sizeof.DWORD]
      mov         [Enemy.Bullet.x + ecx * sizeof.DWORD], eax
      mov         eax, [Enemy.y + ecx * sizeof.DWORD]
      add         eax, [Enemy.height]
      mov         [Enemy.Bullet.y + ecx * sizeof.DWORD], eax
      ret
endp

proc Game.Run.Update.EBullet uses ecx esi eax
      mov         esi, [MainWindow.ClientRect.bottom]
      xor         ecx, ecx
.update_ebullet:
      cmp         [Enemy.activity + ecx * sizeof.DWORD], ENEMY_ACTIVE
      jne         .continue
      mov         eax, [Enemy.y + ecx * sizeof.DWORD]
      add         eax, [Enemy.height]
      cmp         eax , esi
      ja          .continue
      add         [Enemy.Bullet.y + ecx * sizeof.DWORD], EBULLET_DIST
      cmp         [Enemy.Bullet.y + ecx * sizeof.DWORD], esi
      jb          .continue
      stdcall     Game.Run.EnemyBullet, ecx
.continue:
      add         ecx, 1
      cmp         ecx, [Enemy.count]
      jb          .update_ebullet
      ret
endp

proc Game.Run.Bullet uses edi esi ecx ebx eax edx
      cmp         [Player.Bullet.need], 1
      jne         .EndProc

      mov         esi, [Player.Bullet.state]
      add         esi, 1
      mov         eax, [Player.width]
      xor         edx, edx
      div         esi
      mov         esi ,eax
      mov         eax, [Player.Bullet.width]
      shr         eax, 1
      sub         esi, eax
      mov         ebx, esi

      mov         edi, [MainWindow.ClientRect.right]
      xor         ecx, ecx
      xor         esi, esi
.create:
      cmp         [Player.Bullet.x + sizeof.DWORD * ecx], edi
      je          .createnew
      jmp         .continue
.createnew:
      add         esi, 1
      mov         eax, ebx
      xor         edx, edx
      mul         esi
      add         eax, [Player.x]
      mov         [Player.Bullet.x + sizeof.DWORD * ecx], eax
      mov         eax, [Player.y]
      mov         [Player.Bullet.y + sizeof.DWORD * ecx], eax
.continue:
      add         ecx, 1
      cmp         esi, [Player.Bullet.state]
      jnz         .create
      mov         [Player.Bullet.need], 0
      invoke      PlaySound, SND_BULLET, 0, SND_ASYNC or SND_NODEFAULT
.EndProc:
      ret
endp

proc Game.Run.Update.Bullet uses edi ecx
      mov         edi, [MainWindow.ClientRect.right]
      xor         ecx, ecx
.update_pbullet:
      sub         [Player.Bullet.y + ecx * sizeof.DWORD], PBULLET_DIST
      cmp         [Player.Bullet.y + ecx * sizeof.DWORD], 0
      jns         .next_iteration
      mov         [Player.Bullet.x + ecx * sizeof.DWORD], edi
      mov         [Player.Bullet.y + ecx * sizeof.DWORD], 0
    .next_iteration:
      add         ecx, 1
      cmp         ecx, PBULLET_MAX
      jnz         .update_pbullet
      ret
endp

proc Game.Run.Meteor uses esi edi eax edx
      mov         edi, [Player.x]
      mov         [Meteor.x], edi
      mov         [Meteor.y], 0
      stdcall     Random, METEOR_DAMAGE_MIN, METEOR_DAMAGE_MAX
      mov         [Meteor.damage], eax
      imul        eax, 3
      mov         [Meteor.width], eax
      mov         [Meteor.height], eax
      ret
endp

proc Game.Run.Update.Meteor
      add         [Meteor.y], METEOR_DIST
      ret
endp

proc Game.Run.Bonus uses eax edi
      mov         edi, [MainWindow.ClientRect.right]
      sub         edi, [Bonus.width]
      stdcall     Random, 1, edi
      mov         [Bonus.x], eax
      mov         [Bonus.y], 0
      stdcall     Calc.AddMod, [Bonus.hp], 1, BONUS_HP_MAX
      mov         [Bonus.hp], eax
      mov         [Bonus.state], 0
      stdcall     Random, 1, ENEMY_TYPE_COUNT
      sub         eax, 1
      mov         [Bonus.type], eax
      ret
endp

proc Game.Run.Update.Bonus uses eax edx esi
     add          [Bonus.y], BONUS_DIST
     mov          eax, [Bonus.state]
     add          eax, 1
     xor          edx, edx
     mov          esi, BONUS_STATE_COUNT
     div          esi
     mov          [Bonus.state], edx
     ret
endp