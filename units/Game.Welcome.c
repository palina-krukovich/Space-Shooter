proc Game.Welcome uses eax
       mov      [Game.state], GS_WELCOME
       stdcall  Game.Init
       stdcall  Animation.Proton
       invoke   GetTickCount
       mov      [Timer.Update.TickCount], eax
       mov      [Timer.Background.TickCount], eax
       invoke   PlaySound, SND_START, 0, SND_ASYNC or SND_NODEFAULT
       ret
endp

proc Game.Welcome.Update uses eax esi ,\
       TickCount
       mov      esi, [TickCount]
       mov      eax, [Timer.Update.TickCount]
       add      eax, [TIMER_UPDATE]
       cmp      eax, esi
       ja       .EndProc
       stdcall  Game.Welcome.Update.ProcessInput
       stdcall  Animation.Proton.Update
       mov      [Timer.Update.TickCount], esi
       invoke   InvalidateRect, [MainWindow.hWnd], 0, 0
.EndProc:
       ret
endp

proc Animation.Proton
       mov      [Animation.Proton.state], 0
       ret
endp

proc Animation.Proton.Update uses eax edx esi edi
       locals
          Cursor_Pos    POINT
       endl
       ;get cursor position
       lea      edi, [Cursor_Pos]
       invoke   GetCursorPos, edi
       mov      esi, [Cursor_Pos.x]
       mov      eax, [Animation.Proton.width]
       shr      eax, 1
       sub      esi, eax
       mov      [Animation.Proton.x], esi
       mov      esi, [Cursor_Pos.y]
       mov      eax, [Animation.Proton.width]
       shr      eax, 1
       sub      esi, eax
       mov      [Animation.Proton.y], esi
       mov      eax, [Animation.Proton.state]
       add      eax, 1
       mov      esi, ANIMATION_PROTON_STATE_MAX
       xor      edx, edx
       div      esi
       mov      [Animation.Proton.state], edx
       ret
endp

proc Game.Welcome.Update.ProcessInput uses eax esi edi
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
       stdcall  Game.CheckCoordinates, [Cursor_Pos.x], [Cursor_Pos.y], [Welcome.Start.left], [Welcome.Start.top], [Welcome.Start.right], [Welcome.Start.bottom]
       mov      [Welcome.Start.State], eax
       test     eax, esi     ;if cursor is under button (eax) and is button is down(esi) - do something
       jnz      .GS_Run
       stdcall  Game.CheckCoordinates, [Cursor_Pos.x], [Cursor_Pos.y], [Welcome.Exit.left], [Welcome.Exit.top], [Welcome.Exit.right], [Welcome.Exit.bottom]
       mov      [Welcome.Exit.State], eax
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
