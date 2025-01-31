embedder_url = 'https://storage.googleapis.com/flutter_infra_release/flutter/e672b006cb34c921db85b8e2f482ed3144a4574b/linux-x64/linux-x64-embedder.zip'
flutter_linux_embedder = custom_target('flutter_linux_embedder',
                                       output: 'linux-x64-embedder.zip',
                                       command: ['wget', embedder_url, '-O', '@OUTPUT@'])
flutter_header = custom_target('flutter_header',
                               output: 'flutter_embedder.h',
                               command: ['unzip', '-o', '@OUTDIR@/linux-x64-embedder.zip', 'flutter_embedder.h', '-d', '@OUTDIR@'],
                               depends: flutter_linux_embedder)
flutter_engine = custom_target('flutter_engine',
                               output: 'libflutter_engine.so',
                               command: ['unzip', '-o', '@OUTDIR@/linux-x64-embedder.zip', 'libflutter_engine.so', '-d', '@OUTDIR@'],
                               depends: flutter_linux_embedder)

exe = executable('flicker',
                 'main.c',
                 flutter_header,
                 include_directories: include_directories('.'),
                 link_with: flutter_engine,
                 install: true)
