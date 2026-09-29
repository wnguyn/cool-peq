SUPER IMPORTANT COMMAND!


ffmpeg -i input.flac \
  -ar 48000 -ac 1 -c:a pcm_s16le -f s16le input.pcm
