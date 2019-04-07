proc Game.Pause uses eax
       mov      [Game.state], GS_PAUSE
       invoke   GetTickCount
       mov      [Timer.Update.TickCount], eax
       ret
endp

proc Game.Pause.Update uses esi eax,\
       TickCount
       mov      esi, [TickCount]
       mov      eax, [Timer.Update.TickCount]
       add      eax, [TIMER_UPDATE]
       cmp      eax, esi
       ja       .EndProc
       stdcall  Game.Pause.Update.ProcessInput
       stdcall  Animation.Proton.Update
       mov      [Timer.Update.TickCount], esi
       invoke   InvalidateRect, [MainWindow.hWnd], 0, 0
.EndProc:
       ret
endp

proc Game.Pause.Update.ProcessInput uses eax esi edi
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
       stdcall  Game.CheckCoordinates, [Cursor_Pos.x], [Cursor_Pos.y], [Pause.Continue.left], [Pause.Continue.top], [Pause.Continue.right], [Pause.Continue.bottom]
       mov      [Pause.Continue.State], eax
       test     eax, esi     ;if cursor is under button (eax) and is button is down(esi) - do something
       jnz      .GS_Run
       stdcall  Game.CheckCoordinates, [Cursor_Pos.x], [Cursor_Pos.y], [Pause.Exit.left], [Pause.Exit.top], [Pause.Exit.right], [Pause.Exit.bottom]
       mov      [Pause.Exit.State], eax
       test     eax, esi
       jnz      .Exit
       stdcall  Game.CheckCoordinates, [Cursor_Pos.x], [Cursor_Pos.y], [Sound.left], [Sound.top], [Sound.right], [Sound.bottom]
       mov      [Sound.State], eax
       test     eax, esi
       jnz      .SoundStateChange
       jmp      .EndProc
.GS_Run:
       mov      [Game.state], GS_RUN
       invoke   GetTickCount
       mov      [Timer.EWave.TickCount], eax
       mov      [Timer.Bullet.TickCount], eax
       mov      [Timer.Meteor.TickCount], eax
       mov      [Timer.Bonus.TickCount], eax
       mov      [Timer.Score.TickCount], eax
       mov      [Timer.Animation.TickCount], eax
       mov      [Timer.Update.TickCount], eax
       jmp      .EndProc
.Exit:
       invoke   SendMessage, [MainWindow.hWnd], WM_DESTROY, 0, 0
       jmp      .EndProc
.SoundStateChange:
       ;stdcall  Sound.ChangeState
.EndProc:
       ret
endp
