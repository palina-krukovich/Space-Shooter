format PE GUI 4.0
entry WinMain
include 'win32w.inc'
include 'units\Game.h'

section '.code' code readable writeable

proc WinMain
       locals
          Msg   MSG
       endl

       invoke   GetModuleHandle, 0
       mov      [MainWindow.WindowClassEx.hInstance], eax
       stdcall  MainWindow.Create

       lea      edi, [Msg]
.MsgLoop:
       invoke   PeekMessage, edi, 0, 0, 0, PM_NOREMOVE
       test     eax, eax
       jz       .Idle
       invoke   GetMessage, edi, 0, 0, 0
       test     eax, eax
       jz       .EndMsgLoop
       invoke   DispatchMessage, edi
       jmp      .MsgLoop
.Idle:
       invoke   GetTickCount
       mov      esi, eax

       mov      eax, [Timer.Background.TickCount]
       add      eax, [TIMER_BACKGROUND]
       cmp      eax, esi
       ja       .state
       stdcall  Game.Background.Update
       mov      [Timer.Background.TickCount], esi
.state:
       cmp      [Game.state], GS_WELCOME
       je       .welcome
       cmp      [Game.state], GS_PAUSE
       je       .pause
       cmp      [Game.state], GS_GAMEOVER
       je       .gameover
       cmp      [Game.state], GS_RUN
       je       .run
       jmp      .MsgLoop
.welcome:
       stdcall  Game.Welcome.Update, esi
       jmp      .MsgLoop
.pause:
       stdcall  Game.Pause.Update, esi
       jmp      .MsgLoop
.gameover:
       stdcall  Game.GameOver.Update, esi
       jmp      .MsgLoop
.run:
       stdcall  Game.Run.Update, esi
       jmp      .MsgLoop
.EndMsgLoop:
       stdcall  Game.SaveRecord
       invoke   ExitProcess, 0
endp

include 'units\Game.c'
include 'units\MainWindow.c'
include 'units\Calculate.c'

section '.data' data readable writeable

include 'units\MainWindow.d'
include 'units\Game.d'
include 'units\Calculate.d'

section '.idata' data import readable writeable
include 'units\Game.di'