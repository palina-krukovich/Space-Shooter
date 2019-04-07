include 'units\Game.Welcome.c'
include 'units\Game.Pause.c'
include 'units\Game.GameOver.c'
include 'units\Game.Run.c'

proc Game.Init
     stdcall    Game.LoadImages
     stdcall    Game.InitGraphics
     stdcall    Calc.Coordinates
     stdcall    Random.Init
     stdcall    Game.LoadRecord
     ret
endp

proc Game.LoadRecord
       invoke   CreateFile, FRECORD, GENERIC_READ + GENERIC_WRITE, FILE_SHARE_READ, 0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0
       mov      [Record.hf], eax
       invoke   GetLastError
       test     eax, eax
       jz       .CreateNew
       invoke   ReadFile, [Record.hf], Game.Record, 4, BYTESWRITTEN, 0
       jmp      .EndProc
.CreateNew:
       invoke   WriteFile, [Record.hf], Game.Record, 4, BYTESWRITTEN, 0
.EndProc:
       invoke   CloseHandle, [Record.hf]
       ret
endp

proc Game.SaveRecord
       invoke   CreateFile, FRECORD, GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0
       mov      [Record.hf], eax
       invoke   WriteFile, [Record.hf], Game.Record, 4, BYTESWRITTEN, 0
       invoke   CloseHandle, [Record.hf]
       ret
endp

proc Game.LoadImages uses eax esi edi
     invoke     LoadImageW, 0, IMG_BG, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE
     mov        [Background.hbm], eax

     invoke     LoadImageW, 0, IMG_ENEMY, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE
     mov        [Enemy.hbm], eax

     invoke     LoadImageW, 0, IMG_BONUS, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE
     mov        [Bonus.hbm], eax

     invoke     LoadImageW, 0, IMG_PLAYER, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE
     mov        [Player.hbm], eax

     invoke     LoadImageW, 0, IMG_BOSS, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE
     mov        [Boss.hbm], eax

     invoke     LoadImageW, 0, IMG_PBULLET, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE
     mov        [Player.Bullet.hbm], eax

     invoke     LoadImageW, 0, IMG_EBULLET, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE
     mov        [Enemy.Bullet.hbm], eax

     invoke     LoadImageW, 0, IMG_EBULLET, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE
     mov        [Enemy.Bullet.hbm], eax

     invoke     LoadImageW, 0, IMG_START, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE
     mov        [Start.hbm], eax
     add        [IMG_START + sizeof.WORD * 7], 1
     invoke     LoadImageW, 0, IMG_START, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE
     mov        [Start.hbm + sizeof.DWORD], eax

     invoke     LoadImageW, 0, IMG_RESTART, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE
     mov        [Restart.hbm], eax
     add        [IMG_RESTART + sizeof.WORD * 7], 1
     invoke     LoadImageW, 0, IMG_RESTART, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE
     mov        [Restart.hbm + sizeof.DWORD], eax

     invoke     LoadImageW, 0, IMG_CONTINUE, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE
     mov        [Continue.hbm], eax
     add        [IMG_CONTINUE + sizeof.WORD * 7], 1
     invoke     LoadImageW, 0, IMG_CONTINUE, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE
     mov        [Continue.hbm + sizeof.DWORD], eax

     invoke     LoadImageW, 0, IMG_EXIT, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE
     mov        [Exit.hbm], eax
     add        [IMG_EXIT + sizeof.WORD * 7], 1
     invoke     LoadImageW, 0, IMG_EXIT, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE
     mov        [Exit.hbm + sizeof.DWORD], eax

     invoke     LoadImageW, 0, IMG_SOUND, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE
     mov        [Sound.hbm], eax
     add        [IMG_SOUND + sizeof.WORD * 7], 1
     invoke     LoadImageW, 0, IMG_SOUND, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE
     mov        [Sound.hbm + sizeof.DWORD], eax
     add        [IMG_SOUND + sizeof.WORD * 7], 1
     invoke     LoadImageW, 0, IMG_SOUND, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE
     mov        [Sound.hbm + sizeof.DWORD * 2], eax

     invoke     LoadImageW, 0, IMG_GO, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE
     mov        [GameOver.hbm], eax

     invoke     LoadImageW, 0, IMG_PLAYER_HP, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE
     mov        [Player.hp.hbm], eax
     invoke     LoadImageW, 0, IMG_ENEMY_HP, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE
     mov        [Enemy.hp.hbm], eax

     invoke     LoadImageW, 0, IMG_METEOR, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE
     mov        [Meteor.hbm], eax

     invoke     LoadImageW, 0, IMG_BOMB, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE
     mov        [Animation.Bomb.hbm], eax
     invoke     LoadImageW, 0, IMG_BOMB1, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE
     mov        [Animation.Bomb.hbm + sizeof.DWORD], eax

     invoke     LoadImageW, 0, IMG_PROTON, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE
     mov        [Animation.Proton.hbm], eax

     invoke     LoadImageW, 0, IMG_WELCOME, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE
     mov        [Welcome.hbm], eax
     ret
endp

proc Game.InitGraphics uses esi eax
     invoke   GetDC, [MainWindow.hWnd]
     mov      esi, eax
     invoke   CreateCompatibleDC, esi
     mov      [Buffer.hdc], eax
     invoke   CreateCompatibleDC, esi
     mov      [Memory.hdc], eax
     invoke   CreateCompatibleBitmap, esi, [MainWindow.ClientRect.right], [MainWindow.ClientRect.bottom]
     mov      [Buffer.hbm], eax
     invoke   CreateFont, 16,0,0,0,0,FALSE,FALSE,FALSE,ANSI_CHARSET,OUT_RASTER_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FIXED_PITCH+FF_DONTCARE,NULL
     mov      [hfont], eax
     invoke   CreateSolidBrush, $000000FF
     mov      [Red.hbr], eax
     invoke   CreateSolidBrush, $00000000
     mov      [Black.hbr], eax
     invoke   CreatePen, PS_SOLID, 1, $000000FF
     mov      [Red.hp], eax
     invoke   CreatePen, PS_SOLID, 1, $00000000
     mov      [Black.hp], eax
     invoke   ReleaseDC, 0, esi
     ret
endp

proc Game.Draw uses edi eax esi ebx
     locals
        bm    BITMAP
     endl
     lea      edi, [bm]
.Background:
     invoke   GetObject, [Background.hbm], sizeof.BITMAP, edi
     invoke   SelectObject, [Buffer.hdc], [Buffer.hbm]
     invoke   SetStretchBltMode, [Buffer.hdc], HALFTONE
     invoke   SelectObject, [Memory.hdc], [Background.hbm]
     mov      eax, [Background.state]
     imul     eax, BG_SPEED
     invoke   TransparentBlt, [Buffer.hdc], 0, 0, [MainWindow.ClientRect.right], [MainWindow.ClientRect.bottom], [Memory.hdc], 0, eax, [bm.bmWidth], [bm.bmWidth], $00000000

     cmp      [Game.state], GS_WELCOME
     je       .Welcome
     cmp      [Game.state], GS_PAUSE
     je       .Pause
     cmp      [Game.state], GS_GAMEOVER
     je       .GameOver
     cmp      [Game.state], GS_RUN
     je       .Run
     jmp      .EndProc
.Welcome:
     stdcall  Game.Draw.Button, Start.hbm, [Welcome.Start.left], [Welcome.Start.top], [Welcome.Start.right], [Welcome.Start.bottom], [Welcome.Start.State]
     stdcall  Game.Draw.Button, Exit.hbm, [Welcome.Exit.left], [Welcome.Exit.top], [Welcome.Exit.right], [Welcome.Exit.bottom], [Welcome.Exit.State]
     invoke   GetObject, [Animation.Proton.hbm], sizeof.BITMAP, edi
     invoke   SelectObject, [Memory.hdc], [Animation.Proton.hbm]
     mov      eax, [Animation.Proton.state]
     imul     eax, 100
     invoke   TransparentBlt, [Buffer.hdc], [Animation.Proton.x], [Animation.Proton.y], [Animation.Proton.width], [Animation.Proton.height], [Memory.hdc], eax, 0, 100, [bm.bmHeight], $00000000
     invoke   GetObject, [Welcome.hbm], sizeof.BITMAP, edi
     invoke   SelectObject, [Memory.hdc], [Welcome.hbm]
     invoke   TransparentBlt, [Buffer.hdc], [Welcome.rect.left], [Welcome.rect.top], [Welcome.rect.right], [Welcome.rect.bottom], [Memory.hdc], 0, 0, [bm.bmWidth], [bm.bmHeight], $00000000
     jmp      .EndProc
.Pause:
     stdcall  Game.Draw.Button, Continue.hbm, [Pause.Continue.left], [Pause.Continue.top], [Pause.Continue.right], [Pause.Continue.bottom], [Pause.Continue.State]
     stdcall  Game.Draw.Button, Exit.hbm, [Pause.Exit.left], [Pause.Exit.top], [Pause.Exit.right], [Pause.Exit.bottom], [Pause.Exit.State]
     invoke   GetObject, [Animation.Proton.hbm], sizeof.BITMAP, edi
     invoke   SelectObject, [Memory.hdc], [Animation.Proton.hbm]
     mov      eax, [Animation.Proton.state]
     imul     eax, 100
     invoke   TransparentBlt, [Buffer.hdc], [Animation.Proton.x], [Animation.Proton.y], [Animation.Proton.width], [Animation.Proton.height], [Memory.hdc], eax, 0, 100, [bm.bmHeight], $00000000
     jmp      .EndProc
.GameOver:
     invoke   GetObject, [GameOver.hbm], sizeof.BITMAP, edi
     invoke   SelectObject, [Memory.hdc], [GameOver.hbm]
     invoke   TransparentBlt, [Buffer.hdc], [GameOver.rect.left], [GameOver.rect.top], [GameOver.rect.right], [GameOver.rect.bottom], [Memory.hdc], 0, 0, [bm.bmWidth], [bm.bmHeight], $00000000
     stdcall  Game.Draw.Button, Restart.hbm, [GameOver.Restart.left], [GameOver.Restart.top], [GameOver.Restart.right], [GameOver.Restart.bottom], [GameOver.Restart.State]
     stdcall  Game.Draw.Button, Exit.hbm, [GameOver.Exit.left], [GameOver.Exit.top], [GameOver.Exit.right], [GameOver.Exit.bottom], [GameOver.Exit.State]
     invoke   GetObject, [Animation.Proton.hbm], sizeof.BITMAP, edi
     invoke   SelectObject, [Memory.hdc], [Animation.Proton.hbm]
     mov      eax, [Animation.Proton.state]
     imul     eax, 100
     invoke   TransparentBlt, [Buffer.hdc], [Animation.Proton.x], [Animation.Proton.y], [Animation.Proton.width], [Animation.Proton.height], [Memory.hdc], eax, 0, 100, [bm.bmHeight], $00000000
     jmp      .EndProc
.Run:
   .player:
     invoke   GetObject, [Player.hbm], sizeof.BITMAP, edi
     invoke   SelectObject, [Memory.hdc], [Player.hbm]
     mov      eax, [Player.state]
     imul     eax, 47
     invoke   TransparentBlt, [Buffer.hdc], [Player.x], [Player.y], [Player.width], [Player.height], [Memory.hdc], eax, 0, 47, [bm.bmHeight], $00000000
     ;player hp
     invoke   SelectObject, [Memory.hdc], [Player.hp.hbm]
     invoke   GetObject, [Player.hp.hbm], sizeof.BITMAP, edi
     mov      eax, [Player.hp.ProgressBar.width]
     imul     eax, [Player.hp]
     xor      edx, edx
     mov      esi, PLAYER_HP_MAX
     div      esi
     invoke   StretchBlt, [Buffer.hdc], [Player.hp.ProgressBar.x], [Player.hp.ProgressBar.y], eax, [Player.hp.ProgressBar.height], [Memory.hdc], 0, 0, [bm.bmWidth], [bm.bmHeight], SRCCOPY

     invoke   GetObject,[Player.Bullet.hbm], sizeof.BITMAP, edi
     invoke   SelectObject, [Memory.hdc], [Player.Bullet.hbm]
     xor      esi, esi
   .bullet:
     invoke   TransparentBlt, [Buffer.hdc], [Player.Bullet.x + esi * sizeof.DWORD], [Player.Bullet.y + esi * sizeof.DWORD], [Player.Bullet.width], [Player.Bullet.height], [Memory.hdc], 0, 0, [bm.bmWidth], [bm.bmHeight], $00000000
     add      esi, 1
     cmp      esi, PBULLET_MAX
     jb       .bullet

     invoke   GetObject, [Enemy.hbm], sizeof.BITMAP, edi
     invoke   SelectObject, [Memory.hdc], [Enemy.hbm]
     xor      esi, esi
   .enemy:
     mov      eax, [Enemy.type + esi * sizeof.DWORD]
     imul     eax, 256
     mov      ebx, [Enemy.state + esi * sizeof.DWORD]
     imul     ebx, 256
     invoke   TransparentBlt, [Buffer.hdc], [Enemy.x + esi * sizeof.DWORD], [Enemy.y + esi * sizeof.DWORD], [Enemy.width], [Enemy.height], [Memory.hdc], ebx, eax, 256, 256, $00000000
     add      esi, 1
     cmp      esi, [Enemy.count]
     jb       .enemy

     ;enemy hp
     invoke   SelectObject, [Memory.hdc], [Enemy.hp.hbm]
     invoke   GetObject, [Enemy.hp.hbm], sizeof.BITMAP, edi
     xor      esi, esi
    .enemy_hp:
     cmp      [Enemy.activity + esi * sizeof.DWORD], ENEMY_ACTIVE
     jne      .ehp_continue
     mov      eax, [Enemy.width]
     imul     eax, [Enemy.hp + esi * sizeof.DWORD]
     xor      edx, edx
     div      [Enemy.starthp + esi * sizeof.DWORD]
     invoke   StretchBlt, [Buffer.hdc], [Enemy.x + esi * sizeof.DWORD], [Enemy.y + esi * sizeof.DWORD], eax, 5, [Memory.hdc], 0, 0, [bm.bmWidth], [bm.bmHeight], SRCCOPY
    .ehp_continue:
     add      esi, 1
     cmp      esi, [Enemy.count]
     jb       .enemy_hp

     invoke   GetObject, [Enemy.Bullet.hbm], sizeof.BITMAP, edi
     invoke   SelectObject, [Memory.hdc], [Enemy.Bullet.hbm]
     xor      esi, esi
   .enemy_bullet:
     mov      eax, [Enemy.type + esi * sizeof.DWORD]
     imul     eax, 16
     invoke   TransparentBlt, [Buffer.hdc], [Enemy.Bullet.x + esi * sizeof.DWORD], [Enemy.Bullet.y + esi * sizeof.DWORD], [Enemy.Bullet.width], [Enemy.Bullet.height], [Memory.hdc], eax, 0, 16, [bm.bmHeight], $00000000
     add      esi, 1
     cmp      esi, [Enemy.count]
     jb       .enemy_bullet
     ;meteor
     invoke   GetObject, [Meteor.hbm], sizeof.BITMAP, edi
     invoke   SelectObject, [Memory.hdc], [Meteor.hbm]
     invoke   TransparentBlt, [Buffer.hdc], [Meteor.x], [Meteor.y], [Meteor.width], [Meteor.height], [Memory.hdc], 0, 0, [bm.bmWidth], [bm.bmHeight], $00000000
     ;bonus
     invoke   GetObject, [Bonus.hbm], sizeof.BITMAP, edi
     invoke   SelectObject, [Memory.hdc], [Bonus.hbm]
     mov      esi, [Bonus.state]
     imul     esi, 32
     mov      eax, [Bonus.type]
     imul     eax, 32
     invoke   TransparentBlt, [Buffer.hdc], [Bonus.x], [Bonus.y], [Bonus.width], [Bonus.height], [Memory.hdc], esi, eax, 32, 32, $00000000
     ;score
     invoke   SetBkColor, [Buffer.hdc], TRANSPARENT
     invoke   SetTextColor,[Buffer.hdc], $00FFFFFF
     stdcall  UIntToStr, SCORE + 7 * 2, [Game.Score]
     stdcall  UIntToStr, RECORD + 8 * 2, [Game.Record]
     invoke   TextOut, [Buffer.hdc], 0, 0, SCORE, 15
     invoke   TextOut, [Buffer.hdc], 0, 30, RECORD, 15
     ;enemy wave indicator
     invoke   TextOut, [Buffer.hdc], [Enemy.WaveIndicator.x], [Enemy.WaveIndicator.y], E_WAVE, 11
     mov      [E_WAVE_N], ' '
     mov      [E_WAVE_N + 2], ' '
     stdcall  UIntToStr, E_WAVE_N, [Game.WaveCount]
     invoke   TextOut, [Buffer.hdc], [Enemy.WaveIndicator.x + 4], [Enemy.WaveIndicator.y], E_WAVE_N, 2
     ;player hp indicator
     invoke   TextOut, [Buffer.hdc], [Player.hpIndicator.x], [Player.hpIndicator.y], HP, 15
     mov      [HP_NOW], ' '
     mov      [HP_NOW + 2], ' '
     mov      [HP_NOW + 4], ' '
     stdcall  UIntToStr, HP_NOW, [Player.hp]
     invoke   TextOut, [Buffer.hdc], [Player.hpIndicator.x + 4], [Player.hpIndicator.y], HP_NOW, 3
     invoke   TextOut, [Buffer.hdc], [Player.hpIndicator.x + 4 * 2], [Player.hpIndicator.y], HP_MAX, 5
     ;bomb
     invoke   GetObject, [Animation.Bomb.hbm], sizeof.BITMAP, edi
     xor      esi, esi
    .bomb:
     mov      eax, [Animation.Bomb.IsActive + esi * sizeof.DWORD]
     test     eax, eax
     jz       .bomb_continue
     mov      ecx, [Animation.Bomb.type + esi * sizeof.DWORD]
     invoke   SelectObject, [Memory.hdc], [Animation.Bomb.hbm + ecx * sizeof.DWORD]
     mov      eax, [Animation.Bomb.state + esi * sizeof.DWORD]
     xor      edx, edx
     imul     eax, 80
     invoke   TransparentBlt, [Buffer.hdc], [Animation.Bomb.x + esi * sizeof.DWORD], [Animation.Bomb.y + esi * sizeof.DWORD], [Animation.Bomb.width], [Animation.Bomb.height], [Memory.hdc], eax, 0, 80, 80, $00000000
    .bomb_continue:
     add      esi, 1
     cmp      esi, ANIMATION_BOMB_MAX
     jb       .bomb
.EndProc:
     ret
endp

proc Game.Draw.Button uses edi esi eax,\
     button.hbm, x, y, width, height, state
     locals
        bm    BITMAP
     endl
     lea      edi, [bm]
     mov      esi, [button.hbm]
     invoke   GetObject, [esi], sizeof.BITMAP, edi
     mov      eax, [state]
     invoke   SelectObject, [Memory.hdc], [esi + eax * 4]
     invoke   TransparentBlt, [Buffer.hdc], [x], [y], [width], [height], [Memory.hdc], 0, 0, [bm.bmWidth], [bm.bmHeight], $00000000
     ret
endp

proc Game.Background.Update uses eax esi
     mov      eax, [Background.state]
     add      eax, 1
     mov      esi, BG_STATE_COUNT
     div      esi
     mov      [Background.state], edx
     ret
endp
