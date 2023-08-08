## spcplayer
### An [.SPC](http://www.zophar.net/music/spc.html) music player

#### Static Linux 32-bit binary

Included is a statically linked 32-bit Linux binary.

#### Compilation

The SPC emulator is in x86 32-bit assembly, so the result is a 32-bit
application. You need to have a 32-bit libc installed before trying to
attempt to build yourself. zlib is included.  

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
zlib Copyright (C) 1995-2022 by Jean-loup Gailly and Mark Adler. See LICENSE for details.  
