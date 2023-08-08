## spcplayer
### An [.SPC](www.zophar.net/music/spc.html) music player

#### Compilation

The SPC emulator is in x86 32-bit assembly, so the result is a 32-bit
application.
Make sure you have the 32-bit zlib devel ipackage installed before attempting
to build.


```
make
```

Uses OSS for sound output. On modern systems, use a 32-bit aoss or osspd
with your preferred back-end. Tested with osspd-alsa.

#### Usage
    
```
./spcplayer filename.spc
```

#### Authors

dsp emulation and decoding Copyright (C) 2003 by Brad Martin. Licensed under the GPL-2 license. See COPYING for details.  
spc emulation Copyright (C) 2002, 2003 by Charles Bilyue. Licensed under The Clarified Artistic License. See LICENSE for details.  
spcplayer Copyright (C) 2003 by Stephen Melvin Jr.  
