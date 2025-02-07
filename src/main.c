#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>

#include "flutter_embedder.h"

typedef FlutterEngineResult (*FlutterEngineGetProcAddressesFnPtr)(
    FlutterEngineProcTable *table);

static bool present_cb(void *user_data, const void *allocation,
                       size_t row_bytes, size_t height) {
  (void)user_data;
  (void)allocation;
  (void)row_bytes;
  (void)height;
  fprintf(stderr, "present_cb\n");
  return true;
}

static void platform_message_cb(const FlutterPlatformMessage *message,
                                void *user_data) {
  (void)message;
  (void)user_data;
  fprintf(stderr, "platform_message_cb\n");
}

static void create_root_isolate_cb(void *user_data) {
  (void)user_data;
  fprintf(stderr, "create_root_isolate_cb\n");
}

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s [directory]\n", argv[0]);
    return 1;
  }

  char *dir = argv[1];

  char engine_library_path[1024];
  snprintf(engine_library_path, 1024, "%s/libflutter_engine.so", dir);

  char icu_data_path[1024];
  snprintf(icu_data_path, 1024, "%s/icudtl.dat", dir);

  FlutterRendererConfig renderer_config;
  renderer_config.type = kSoftware;
  renderer_config.software.struct_size = sizeof(FlutterSoftwareRendererConfig);
  renderer_config.software.surface_present_callback = present_cb;

  FlutterProjectArgs project_args;
  project_args.struct_size = sizeof(FlutterProjectArgs);
  project_args.assets_path = dir;
  project_args.icu_data_path = icu_data_path;
  project_args.command_line_argc = 0;
  project_args.command_line_argv = NULL;
  project_args.platform_message_callback = platform_message_cb;
  project_args.vm_snapshot_data = NULL;
  project_args.vm_snapshot_data_size = 0;
  project_args.vm_snapshot_instructions = NULL;
  project_args.vm_snapshot_instructions_size = 0;
  project_args.isolate_snapshot_data = NULL;
  project_args.isolate_snapshot_data_size = 0;
  project_args.isolate_snapshot_instructions = NULL;
  project_args.isolate_snapshot_instructions_size = 0;
  project_args.root_isolate_create_callback = create_root_isolate_cb;
  project_args.persistent_cache_path = NULL;
  project_args.is_persistent_cache_read_only = false;
  project_args.vsync_callback = NULL;
  project_args.custom_dart_entrypoint = NULL;
  project_args.custom_task_runners = NULL;
  project_args.shutdown_dart_vm_when_done = true;
  project_args.compositor = NULL;
  project_args.dart_old_gen_heap_size = -1;
  project_args.aot_data = NULL;
  project_args.compute_platform_resolved_locale_callback = NULL;
  project_args.dart_entrypoint_argc = 0;
  project_args.dart_entrypoint_argv = NULL;
  project_args.log_message_callback = NULL;
  project_args.log_tag = NULL;
  project_args.on_pre_engine_restart_callback = NULL;
  project_args.update_semantics_callback2 = NULL;
  project_args.channel_update_callback = NULL;

  // Clear deprecated callbacks.
  project_args.update_semantics_node_callback = NULL;
  project_args.update_semantics_custom_action_callback = NULL;
  project_args.update_semantics_callback = NULL;

  FlutterEngine engine;
  FlutterEngineResult result = FlutterEngineInitialize(
      FLUTTER_ENGINE_VERSION, &renderer_config, &project_args, NULL, &engine);
  if (result != kSuccess) {
    fprintf(stderr, "Unable to initialize engine\n");
    return 1;
  }

  result = FlutterEngineRunInitialized(engine);
  if (result != kSuccess) {
    fprintf(stderr, "Unable to run engine\n");
    return 1;
  }

  select(0, NULL, NULL, NULL, NULL);

  return 0;
}
