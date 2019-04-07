library kernel32, 'kernel32.dll',\
        gdi32,    'gdi32.dll',\
        user32,   'user32.dll',\
        winmm,    'winmm.dll',\
        msimg32,  'Msimg32.dll'

include 'api\kernel32.inc'
include 'api\gdi32.inc'
include 'api\user32.inc'

import winmm,\
       PlaySound,       'PlaySoundW'
import msimg32,\
       TransparentBlt, 'TransparentBlt'