proc Game.GameOver
       mov        [Game.state], GS_GAMEOVER
       ret
endp

proc Game.GameOver.Update,\
       TickCount
       mov      esi, [TickCount]
       mov      eax, [Timer.Update.TickCount]
       add      eax, [TIMER_UPDATE]
       cmp      eax, esi
       ja       .EndProc
       stdcall  Game.GameOver.Update.ProcessInput
       stdcall  Animation.Proton.Update
       mov      [Timer.Update.TickCount], esi
       invoke   InvalidateRect, [MainWindow.hWnd], 0, 0
.EndProc:
     ret
endp

proc Game.GameOver.Update.ProcessInput uses eax esi edi
       locals
          Cursor_Pos    POINT
       endl
       ;check if the left mouse button is down
       invoke   GetKeyState, VK_LBUTTON
       and      eax, $8000
       shr      eax, 15
       mov      esi, eax
       ;get cursor position
       lea      edi, [Cursor_Pos]
       invoke   GetCursorPos, edi
       ;check if cursor is under a button
       stdcall  Game.CheckCoordinates, [Cursor_Pos.x], [Cursor_Pos.y], [GameOver.Restart.left], [GameOver.Restart.top], [GameOver.Restart.right], [GameOver.Restart.bottom]
       mov      [GameOver.Restart.State], eax
       test     eax, esi     ;if cursor is under button (eax) and is button is down(esi) - do something
       jnz      .GS_Run
       stdcall  Game.CheckCoordinates, [Cursor_Pos.x], [Cursor_Pos.y], [GameOver.Exit.left], [GameOver.Exit.top], [GameOver.Exit.right], [GameOver.Exit.bottom]
       mov      [GameOver.Exit.State], eax
       test     eax, esi
       jnz      .Exit
       stdcall  Game.CheckCoordinates, [Cursor_Pos.x], [Cursor_Pos.y], [Sound.left], [Sound.top], [Sound.right], [Sound.bottom]
       mov      [Sound.State], eax
       test     eax, esi
       jnz      .SoundStateChange
       jmp      .EndProc
.GS_Run:
       stdcall  Game.Run
       jmp      .EndProc
.Exit:
       invoke   SendMessage, [MainWindow.hWnd], WM_DESTROY, 0, 0
       jmp      .EndProc
.SoundStateChange:
       ;stdcall  Sound.ChangeState
.EndProc:
       ret
endp