
/* Stephen B Melvin Jr, <stephenbmelvin@gmail.com>
 * Copyright (C) 2003
 * Version 0.2
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/soundcard.h>
#include <sys/ioctl.h>
#include "openspc.h"

int main(int argc, char *argv[]) {
    int optionoffset = 0, audio_fd, channels = 2, rformat, rchannels, format =
        AFMT_S16_LE, speed = 32000, fd;
    char *audio_device = "/dev/dsp";
    char ver[] = "0.2";
    char c;
    void *ptr, *buf;
    off_t size;


    if ((argc < 2)) {
        printf("spcplayer version %s\n"
                "usage: spcplayer [sound device] filename.spc\n",
             ver);
        return 1;
    }

    if ((argc > 2)) {
        audio_device = strdup(argv[1]);
        optionoffset++;
    }

    if ((audio_fd = open(audio_device, O_WRONLY, 0)) == -1) {
        fprintf(stderr, "[-] Could not open %s.\n", audio_device);
        return 1;
    }
    printf("[+] Successfully opened %s.\n", audio_device);

    rformat = format;
    if (ioctl(audio_fd, SNDCTL_DSP_SETFMT, &format) == -1) {
        fprintf(stderr, "[-] Could not set sound format.\n");
        return 1;
    }
    if (format != rformat) {
        fprintf(stderr, "[-] Could not set sound format.\n");
        return 1;
    }
    printf("[+] Successfully set sound format.\n");

    rchannels = channels;
    if (ioctl(audio_fd, SNDCTL_DSP_CHANNELS, &channels) == -1) {
        fprintf(stderr, "[-] Could not set channels.\n");
        return 1;
    }
    if (channels != rchannels) {
        fprintf(stderr, "[-] Could not set channels.\n");
        return 1;
    }
    printf("[+] Successfully set channels.\n");

    if (ioctl(audio_fd, SNDCTL_DSP_SPEED, &speed) == -1) {
        fprintf(stderr, "[-] Could not set speed.\n");
        return 1;
    }
    printf("[+] Using speed, {%iHz}\n", speed);

    buf = malloc(32000);

    fd = open(argv[1 + optionoffset], O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "[-] Could not open \'%s\'\n.", argv[1]);
        return 1;
    }

    size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    ptr = malloc(size);
    int ret = read(fd, ptr, size);
    if (ret <0) {
        fprintf(stderr, "error reading file\n");
        return 1;
    }
    close(fd);

    fd = OSPC_Init(ptr, size);

    free(ptr);
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
    printf("[+] Playing SPC, press Enter to quit.\n");

    while ((read(STDIN_FILENO, &c, 1)) <= 0) {
        size = OSPC_Run(-1, buf, 32000);
        int ret = write(audio_fd, buf, size);
        if (ret < 0) {
            fprintf(stderr, "error writing to audio device\n");
            return 1;
        }
    }

    printf("\nGoodbye!\n");
    return 0;
}
