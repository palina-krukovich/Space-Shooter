proc MainWindow.Create
       invoke   LoadCursor, 0, IDC_ARROW
       mov      [MainWindow.WindowClassEx.hCursor], eax
       invoke   RegisterClassEx, MainWindow.WindowClassEx
       invoke   GetSystemMetrics, SM_CXSCREEN
       mov      [MainWindow.ClientRect.right], eax
       invoke   GetSystemMetrics, SM_CYSCREEN
       mov      [MainWindow.ClientRect.bottom], eax

       invoke   CreateWindowEx, 0,MainWindow.ClassName,0,WS_POPUP or WS_VISIBLE,[MainWindow.ClientRect.left],[MainWindow.ClientRect.top],[MainWindow.ClientRect.right],[MainWindow.ClientRect.bottom],0,0,[MainWindow.WindowClassEx.hInstance], 0
       mov      [MainWindow.hWnd], eax
       ret
endp

proc MainWindow.WindowProc uses ebx esi edi,\
       hWnd, uMsg, wParam, lParam
       locals
          PS    PAINTSTRUCT
       endl
       mov      eax, [uMsg]
       cmp      eax, WM_DESTROY
       je       .WMDestroy
       cmp      eax, WM_CREATE
       je       .WMCreate
       cmp      eax, WM_PAINT
       je       .WMPaint
.Default:
       invoke   DefWindowProc, [hWnd], [uMsg], [wParam], [lParam]
       jmp      .EndProc
.WMDestroy:
       invoke   PostQuitMessage, 0
       jmp      .Default
.WMCreate:
       invoke   ShowCursor, 0
       stdcall  Game.Welcome
       jmp      .Default
.WMPaint:
       invoke   GetUpdateRect, [hWnd], 0, 0
       test     eax, eax
       jz       .EndProc

       stdcall  Game.Draw
       lea      edi, [PS]
       invoke   BeginPaint, [hWnd], edi
       invoke   BitBlt, eax, 0, 0, [MainWindow.ClientRect.right], [MainWindow.ClientRect.bottom], [Buffer.hdc], 0, 0, SRCCOPY
       invoke   EndPaint, [hWnd], edi
       jmp      .ReturnZero
.ReturnZero:
       xor      eax, eax
.EndProc:
       ret
endp