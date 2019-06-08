#include "config_LFS.h"

void iniciar_logger(void)
{

	g_logger = log_create("LFS.log", "LFS", 0, LOG_LEVEL_INFO);

	log_info(g_logger, "logger iniciado");
}

void crear_config() {
    config = config_create("LFS.cfg");
}

void leer_config() {
	lfs_config.puerto_lfs = strdup(config_get_string_value(config, "PUERTO_LFS"));
	lfs_config.punto_montaje = strdup(config_get_string_value(config, "PUNTO_MONTAJE"));
	lfs_config.retardo_lfs = config_get_int_value(config, "RETARDO_LFS");
	lfs_config.value_size = config_get_int_value(config, "VALUE_SIZE");
	lfs_config.tiempo_dump = config_get_int_value(config, "TIEMPO_DUMP");

	//	Clausura de la estructura config
	config_destroy(config);
}

void crear_metadata() {
	char* metadata_path;

	metadata_path = generate_path("/Metadata/Metadata", lfs_config.punto_montaje, ".bin");

	log_info(g_logger, "Metadata path is: %s", metadata_path);
    metadata = config_create(metadata_path);

    free(metadata_path);
}

void leer_metadata() {
	BLOCK_SIZE = strdup(config_get_string_value(metadata, "BLOCK_SIZE"));
	BLOCKS = strdup(config_get_string_value(metadata, "BLOCKS"));
	MAGIC_NUMBER = strdup(config_get_string_value(metadata, "MAGIC_NUMBER"));

	//	Clausura de la estructura config
	config_destroy(metadata);
}

void loggear_metadata() {
    log_info(g_logger, "BLOCK SIZE: %s", BLOCK_SIZE);
    log_info(g_logger, "BLOCKS: %s", BLOCKS);
    log_info(g_logger, "MAGIC NUMBER: %s", MAGIC_NUMBER);
}

void loggear_config() {
    log_info(g_logger, "PUERTO LFS: %s", lfs_config.puerto_lfs);
    log_info(g_logger, "PUNTO MONTAJE: %s", lfs_config.punto_montaje);
    log_info(g_logger, "RETARDO LFS: %d", lfs_config.retardo_lfs);
    log_info(g_logger, "TAMANO DE VALUE: %d", lfs_config.value_size);
    log_info(g_logger, "TIEMPO DE DUMP: %d", lfs_config.tiempo_dump);
}

void liberar_config(lfs_cfg lfs_config) {
    free(lfs_config.puerto_lfs);
    free(lfs_config.punto_montaje);
}

void liberar_logger(t_log* g_logger){
	log_destroy(g_logger);
}

void iniciar_config(){
	iniciar_logger();
	crear_config();
	leer_config();
	loggear_config();

	crear_metadata();
	leer_metadata();
	loggear_metadata();
}

void iniciar_montaje(){
	char** folders = string_split(lfs_config.punto_montaje, "/");
	int cant_folders = split_cant_elem(folders);

	char s[100];

	for (int i = 0; i < cant_folders; i++) {
		// Does the directory exist?

		struct stat st = {0};

		if (stat(folders[i], &st) == -1) {
			// Create it
			mkdir(folders[i], 0700);
		}


		log_info(g_logger, "Current directory is: %s \n", getcwd(s, 100));
		chdir(folders[i]);
		log_info(g_logger, "Current mount directory is: %s \n", getcwd(s, 100));
	}
	split_liberar(folders);

//	char *carpeta = "tablas";
//	crear_carpeta(carpeta);
//	carpeta = "bloques";
//	crear_carpeta(carpeta);
//	carpeta = "metadata";
//	crear_carpeta(carpeta);
//
//	//free(carpeta);

}

//void crear_carpeta(char* carpeta){
//	log_info(g_logger,"Directorio %s",carpeta);
//	char* directorio = string_from_format("%s/%s/",lfs_config.punto_montaje,carpeta);
//
//	struct stat st = {0};
//	if (stat(directorio, &st) == -1) {
//		// Create it
//		mkdir(directorio, 0700);
//	}
//	log_info(g_logger,"cree bien %s",directorio);
//	free(directorio);
//}
