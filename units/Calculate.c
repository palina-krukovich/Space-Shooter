proc UIntToStr uses edi esi ecx edx,\
     pStr, Num
     mov        edi, [Num]
     xor        ecx, ecx
     mov        eax, edi
     mov        esi, 10
.loop:
     xor        edx, edx
     div        esi
     push       edx
     add        ecx, 1
     test       eax, eax
     jnz        .loop

     mov        edi, [pStr]
     xor        esi, esi
.loop2:
     pop        eax
     add        eax, 48
     mov        [edi + esi * 2], ax
     add        esi, 1
     sub        ecx, 1
     test       ecx, ecx
     jnz        .loop2
     ret
endp

proc Random.Init uses eax
     invoke     GetTickCount
     mov        [Random.wPrevNumber], eax
     ret
endp

proc Random uses edx ecx,\
     nMinValue, nMaxValue

     xor        edx, edx
     mov        ecx, [nMaxValue]
     sub        ecx, [nMinValue]
     inc        ecx

     invoke     GetTickCount
     add        eax, [Random.wPrevNumber]
     rol        ax, 7
     add        ax, 23
     mov        [Random.wPrevNumber], eax

     div        ecx
     mov        eax, edx
     add        eax, [nMinValue]

     ret
endp

proc Game.CheckCoordinates uses edi esi ebx edx,\
     x, y, left, top, width, height
     mov      esi, [x]
     mov      edi, [y]
     mov      ebx, [left]
     mov      edx, [top]
     cmp      esi, ebx
     js       .Return_FALSE
     cmp      edi, edx
     js       .Return_FALSE
     add      ebx, [width]
     cmp      ebx, esi
     js       .Return_FALSE
     add      edx, [height]
     cmp      edx, edi
     js       .Return_FALSE
.Return_TRUE:
     mov      eax, 1
     jmp      .EndProc
.Return_FALSE:
     xor      eax, eax
.EndProc:
     ret
endp

proc Calc.Coordinates uses esi edi eax
     mov      edi, [MainWindow.ClientRect.right]
     mov      esi, [MainWindow.ClientRect.bottom]

     stdcall  Calc.RelativeValue, esi, 3, 1
     mov      [Welcome.Start.right], eax
     mov      [Welcome.Exit.right], eax
     mov      [Pause.Continue.right], eax
     mov      [Pause.Exit.right], eax
     mov      [GameOver.Restart.right], eax
     mov      [GameOver.Exit.right], eax
     stdcall  Calc.RelativeValue, [Welcome.Start.right], 2, 1
     mov      [Welcome.Start.bottom], eax
     mov      [Welcome.Exit.bottom], eax
     mov      [Pause.Continue.bottom], eax
     mov      [Pause.Exit.bottom], eax
     mov      [GameOver.Restart.bottom], eax
     mov      [GameOver.Exit.bottom], eax
     stdcall  Calc.GetCenterCoord, edi, [Welcome.Start.right]
     mov      [Welcome.Start.left], eax
     mov      [Welcome.Exit.left], eax
     mov      [Pause.Continue.left], eax
     mov      [Pause.Exit.left], eax
     stdcall  Calc.GetCenterCoord, esi, [Welcome.Start.bottom]
     mov      [Welcome.Start.top], eax
     mov      [Pause.Continue.top], eax
     stdcall  Calc.RelativeValue, esi, 3, 2
     mov      [Welcome.Exit.top], eax
     mov      [Pause.Exit.top], eax

     stdcall  Calc.RelativeValue, edi, 3, 1
     mov      [GameOver.Restart.left], eax
     mov      eax, [GameOver.Restart.right]
     shr      eax, 1
     sub      [GameOver.Restart.left], eax
     stdcall  Calc.RelativeValue, edi, 3, 2
     mov      [GameOver.Exit.left], eax
     mov      eax, [GameOver.Exit.right]
     shr      eax, 1
     sub      [GameOver.Exit.left], eax
     stdcall  Calc.RelativeValue, esi, 3, 2
     mov      [GameOver.Restart.top], eax
     mov      [GameOver.Exit.top], eax


     stdcall  Calc.RelativeValue, [Welcome.Exit.bottom], 2, 1
     mov      [Sound.right], eax
     mov      [Sound.bottom], eax
     stdcall  Calc.RelativeValue, esi, 16, 1
     mov      [Sound.left], eax
     stdcall  Calc.RelativeValue, esi, 8, 7
     mov      [Sound.top], eax

     stdcall  Calc.RelativeValue, edi, 16, 1
     mov      [Player.width], eax
     stdcall  Calc.RelativeValue, [Player.width], 2, 3
     mov      [Player.height], eax
     stdcall  Calc.GetCenterCoord, edi, [Player.width]
     mov      [Player.x], eax
     stdcall  Calc.GetCenterCoord, esi, [Player.height]
     mov      [Player.y], eax

     stdcall  Calc.RelativeValue, edi, 14, 1
     mov      [Enemy.width], eax
     mov      [Enemy.height], eax
     stdcall  Calc.GetCenterCoord, esi, [Enemy.height]
     mov      [ENEMY_YMAX], eax

     stdcall  Calc.RelativeValue, edi, 22, 1
     mov      [Meteor.width], eax
     mov      [Meteor.height], eax

     stdcall  Calc.RelativeValue, [Player.width], 9, 1
     mov      [Player.Bullet.width], eax
     stdcall  Calc.RelativeValue, [Player.Bullet.width], 1, 2
     mov      [Player.Bullet.height], eax

     stdcall  Calc.RelativeValue, [Enemy.width], 8,1
     mov      [Enemy.Bullet.width], eax
     stdcall  Calc.RelativeValue, [Enemy.Bullet.width], 1, 2
     mov      [Enemy.Bullet.height], eax

     stdcall  Calc.RelativeValue, edi, 3, 2
     mov      [GameOver.rect.right], eax
     stdcall  Calc.RelativeValue, esi, 3, 2
     mov      [GameOver.rect.bottom], eax
     stdcall  Calc.GetCenterCoord, edi, [GameOver.rect.right]
     mov      [GameOver.rect.left], eax
     stdcall  Calc.GetCenterCoord, esi, [GameOver.rect.bottom]
     stdcall  Calc.RelativeValue, eax, 2, 1
     mov      [GameOver.rect.top], eax

     stdcall  Calc.RelativeValue, edi, 5, 3
     mov      [Welcome.rect.right], eax
     stdcall  Calc.RelativeValue, eax, 4, 1
     mov      [Welcome.rect.bottom], eax
     stdcall  Calc.GetCenterCoord, edi, [Welcome.rect.right]
     mov      [Welcome.rect.left], eax
     stdcall  Calc.RelativeValue, esi, 10, 1
     mov      [Welcome.rect.top], eax


     stdcall  Calc.RelativeValue, edi, 10, 1
     mov      [Player.hp.ProgressBar.width], eax
     mov      [Player.hp.ProgressBar.height], 15
     stdcall  Calc.RelativeValue, edi, 2, 1
     mov      [Player.hpIndicator.x], eax
     add      eax, 120
     mov      [Player.hpIndicator.x + 4], eax
     add      eax, 30
     mov      [Player.hpIndicator.x + 4 * 2], eax
     add      eax, 40
     mov      [Player.hp.ProgressBar.x], eax
     add      eax, 250
     mov      [Enemy.WaveIndicator.x], eax
     add      eax, 110
     mov      [Enemy.WaveIndicator.x + 4], eax
     mov      eax, esi
     sub      eax, 25
     mov      [Player.hpIndicator.y], eax
     mov      [Player.hp.ProgressBar.y], eax
     mov      [Enemy.WaveIndicator.y], eax

     stdcall  Calc.RelativeValue, edi, 17, 1
     mov      [Animation.Proton.width], eax
     mov      [Animation.Proton.height], eax
     ret
endp

proc Calc.RelativeValue uses edx ebx ecx,\
       Value, DivValue, MulValue
       mov      eax, [Value]
       mov      ebx, [DivValue]
       mov      ecx, [MulValue]
       xor      edx, edx
       div      ebx
       mul      ecx
       ret
endp

proc Calc.GetCenterCoord uses ebx,\
       WidthMain, WidthObj
       mov      ebx, [WidthObj]
       shr      ebx, 1
       mov      eax, [WidthMain]
       shr      eax, 1
       sub      eax, ebx
       ret
endp

proc Calc.AddMod uses edx,\
       x, y, p
       mov         eax, [x]
       add         eax, [y]
       xor         edx, edx
       div         [p]
       cmp         eax, 1
       je          .nochange
       mov         eax, edx
       jmp         .EndProc
.nochange:
       mov         eax, [x]
.EndProc:
       ret
endp
